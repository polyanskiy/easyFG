#include <iostream>
#include "b16img2.h"

using namespace std;

int main(int argc, char ** argv) {
	b16img2 iImage(argv[1]);
	iImage.scanBrightness();

	cout<<iImage.integrateImage(1e-6,0,0)<<endl;
	//cout<<"FWHM: "<<iImage.integrateImage(1e-6,1/2)<<endl;
	return 0;
}
