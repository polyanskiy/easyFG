/*
 * derivation of physImage for spiricon beam profiler raw file data 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "physImage.h"

#ifndef __spiricon_h
#define __spiricon_h

using namespace std;

class spiricon : public physImage {

public:
	spiricon(const char *);

	ifstream *ifile;

};

#endif
