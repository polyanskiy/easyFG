/*
 * derivation of physImage for bmp 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "physImage.h"

#ifndef __bmpimg_h
#define __bmpimg_h

using namespace std;

class bmpimg : public physImage {

public:
	bmpimg(const char *);

	ifstream *ifile;

};

#endif
