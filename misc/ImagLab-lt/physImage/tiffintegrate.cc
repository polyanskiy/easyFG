#include <iostream>

#include "physImage.h"
#include "tiffimg.h"

using namespace std;

int main(int argc, char **argv)
{
	tiffimg *my_img;
	my_img = new tiffimg(argv[1]);

	my_img->scanBrightness();
	cout<<my_img->integrateImage(0,0,0)<<endl;
}
