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
	BlockAlignment(int argc, char const *argv[])
	{
		textFileName = argv[1];
		readFile(textFileName, textData);
		setTextSize();

		blockFileName = argv[2];
		readFile(blockFileName, blockData);
		setBlockSize();

		for (int i = 0; i < blockSizeN; ++i)
			for (int j = 0; j < blockSizeM; ++j)
				blockSequence += blockData[i][j];

		// Resize alignment matrix
		int size = blockSequence.size() + 1;
		alignment.resize(size);
		for (int i = 0; i < size; ++i)
		{
			alignment[i].resize(size);
		}

		// Resize similarity matrix
		numberOfSequences = (textSizeN - blockSizeN + 1) * (textSizeM - blockSizeM + 1);
		similarity.resize(numberOfSequences);
		for (int i = 0; i < numberOfSequences; ++i)
		{
			similarity[i].resize(3);
		}

		// cout << "numberOfSequences: " << numberOfSequences << endl;
	};

	~BlockAlignment(){};
	
	// Public methods
	void align();
	void print();

private:
	// Variables
	const char *textFileName;
	const char *blockFileName;
	vector<vector<char> > textData;
	vector<vector<char> > blockData;
	vector<vector<int> > similarity;
	vector< vector<int> > alignment;
	int blockSizeN;
	int blockSizeM;
	int textSizeN;
	int textSizeM;
	int numberOfSequences;
	int sIterator;
	string textSequence;
	string blockSequence;
	string textSequenceResult;
	string blockSequenceResult;

	// Methods
	void readFile(const char *fileName,  vector<vector<char> > &fileData);
	void setBlockSize();
	void setTextSize();
	void getSequence(int n, int m);
	void globalAlignment(string textSequence, string blockSequence);
	int score(const char a, const char b);
	int max(int a, int b, int c);
};

#endif