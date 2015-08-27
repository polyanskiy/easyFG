/*
 * derivation of physImage for b16 support
 */

#include <iostream>
#include <fstream>
#include <Magick++.h>

#include "physImage.h"

#ifndef __IMimg_h
#define __IMimg_h

using namespace std;

inline int swapED (int);
inline short swapED (short);

class IMimg : public physImage {

public:
	IMimg(const char *);

	ifstream *ifile;

};

#endif
