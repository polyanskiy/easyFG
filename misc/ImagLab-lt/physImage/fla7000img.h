/*
 * derivation of physImage for fla7000 image file support
 */

#include <iostream>
#include <fstream>
#include <string>

#include "physImage.h"

#ifndef __fla7000img_h
#define __fla7000img_h

using namespace std;

inline int swapED (int);
inline short swapED (short);

class fla7000img : public physImage {

public:
	fla7000img(const char *);

	ifstream *ifile;

};

#endif
