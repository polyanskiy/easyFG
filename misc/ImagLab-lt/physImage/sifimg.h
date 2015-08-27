/*
 * derivation of physImage for sif (proprietary Andor) support
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "physImage.h"

#ifndef __sifimg_h
#define __sifimg_h

using namespace std;

class sifimg : public physImage {

public:
	sifimg(const char *);

	ifstream *ifile;

	//physImage operator ()
	//{ return *((physImage *)this); }

};

#endif
