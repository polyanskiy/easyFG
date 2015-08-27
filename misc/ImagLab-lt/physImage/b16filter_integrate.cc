#include <iostream>
#include "b16img2.h"

// integrates the pixel-by-pixel product of two images

using namespace std;

int main(int argc, char ** argv) {

	if (argc < 3) {
		cerr<<"Use "<<argv[0]<<" <image1> <image2>"<<endl;
		exit(1);
	}

	b16img2 img1(argv[1]);
	b16img2 img2(argv[2]);

	physImage new_img(&(img1*img2));

	cout<<new_img.integrateImage(1e-6,0,0)<<endl;
	//cout<<"FWHM: "<<iImage.integrateImage(1e-6,1/2)<<endl;
	return 0;
}
