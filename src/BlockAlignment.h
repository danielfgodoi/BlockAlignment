#ifndef _BlockAlignment_h
#define _BlockAlignment_h

#include <fstream>
#include <streambuf>
#include <iostream>
#include <stdlib.h>
using namespace std;

class BlockAlignment
{
public:
	BlockAlignment(){};
	~BlockAlignment(){};

	// Public methods
	void readFile(char const *fileName);

private:
	// Variables
	char *text;

	// Methods
	void parse();
	void align();
	void print();
};

#endif