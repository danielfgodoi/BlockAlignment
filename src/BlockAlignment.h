#ifndef _BlockAlignment_h
#define _BlockAlignment_h

#include <fstream>
#include <streambuf>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class BlockAlignment
{
public:
	BlockAlignment(char const *textFileName, char const *blockFileName)
	{
		textFileName = textFileName;
		readFile(textFileName, text);
		setTextSize();

		blockFileName = blockFileName;
		readFile(blockFileName, block);
		setBlockSize();
	};

	~BlockAlignment(){};

private:
	// Variables
	char *textFileName;
	char *blockFileName;
	vector<vector<char> > text;
	vector<vector<char> > block;
	int blockSizeN;
	int blockSizeM;
	int textSizeN;
	int textSizeM;

	// Methods
	void readFile(const char *fileName,  vector<vector<char> > &fileData);
	void setBlockSize();
	void setTextSize();
	void parse();
	void align();
};

#endif