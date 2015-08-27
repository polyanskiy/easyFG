/*
 * derivation of physImage for pgm
 */

#include <iostream>
#include <fstream>
#include <string>

#include "physImage.h"

extern "C" {
#include <pgm.h>
}

#include <stdio.h>

#ifndef __pgmimg_h
#define __pgmimg_h

using namespace std;

class pgmimg : public physImage {

public:
	pgmimg(const char *);

	ifstream *ifile;

};

#endif
