/*
 * derivation of physImage for b16 support
 */

#include <iostream>
#include <fstream>

#include "physImage.h"

#ifndef __b16img2_h
#define __b16img2_h

using namespace std;

inline int swapED (int);
inline short swapED (short);

class b16img2 : public physImage {

public:
	b16img2(const char *);

	ifstream *ifile;

};

#endif
