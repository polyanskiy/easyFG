#include <iostream>
#include "pgmimg.h"

using namespace std;

int main(int argc, char ** argv) {
	pgmimg iImage(argv[1]);
	iImage.scanBrightness();

	cout<<iImage.integrateImage(1e-6,0,0)<<endl;
	//cout<<"FWHM: "<<iImage.integrateImage(1e-6,1/2)<<endl;
	return 0;
}
