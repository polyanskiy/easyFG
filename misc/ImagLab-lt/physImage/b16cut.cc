#include <iostream>
#include <cmath>

#include "physImage.h"
#include "sifimg.h"

int main(int argc, char **argv)
{
	char *iname, *oname;
	int ulx, uly, lrx, lry;
	int cx, cy, mw;

	physImage *iimg, *oimg;

	if (argc < 6) {
		cout<<"use ./command iname oname cx cy w"<<endl;
		exit(0);
	}

	iname = argv[1];
	oname = argv[2];
	cx = atoi(argv[3]);
	cy = atoi(argv[4]);
	mw = (int)floor(atoi(argv[5])/2);

	ulx = cx-mw;
	uly = cy-mw;
	lrx = cx+mw;
	lry = cy+mw;

	iimg = new sifimg(iname);
	oimg = iimg->subImage(ulx,uly,lrx,lry);
	oimg->writePGM(oname);

}
