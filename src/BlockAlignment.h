#ifndef _BlockAlignment_h
#define _BlockAlignment_h

#include <fstream>
#include <streambuf>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <climits>

using namespace std;

class BlockAlignment
{
public:
	// Class constructor
	BlockAlignment(vector<string> textFileNameList, string blockFileName)
	{
		this->textFileNameList = textFileNameList;
		this->blockFileName = blockFileName;
	};

	// Default destructor
	~BlockAlignment(){};
	
	// Public methods
	void align();

private:
	// Variables
	int blockSizeN;
	int blockSizeM;
	int textSizeN;
	int textSizeM;
	int numberOfSequences;
	int sIterator;
	vector<string> textFileNameList;
	string textFileName;
	string blockFileName;
	string textSequence;
	string blockSequence;
	string textSequenceResult;
	string blockSequenceResult;
	vector<vector<char> > textData;
	vector<vector<char> > blockData;
	vector<vector<int> > similarity;
	vector< vector<int> > alignment;

	// Methods
	void print();
	void readFile(string fileName,  vector<vector<char> > &fileData);
	void setBlockSize();
	void setTextSize();
	void getSequence(int n, int m);
	void globalAlignment(string textSequence, string blockSequence);
	int score(const char a, const char b);
	int max(int a, int b, int c);
};

#endif