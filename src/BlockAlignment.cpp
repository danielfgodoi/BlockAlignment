#include "BlockAlignment.h"
#define breakLine 50

inline void
BlockAlignment::readFile(string fileName,  vector<vector<char> > &fileData, int &maxN, int &maxM, char type)
{
	fileData.clear();
	// ifstream file(fileName, ios::in | ios::binary | ios::ate);
	ifstream file(fileName.c_str());

	if (file)
	{
		ifstream::pos_type fileSize = file.tellg();
		file.seekg(0, ios::beg);
		std::vector<char> data;
		char c;

		if (type == 'b')
		{
			c = '?';
		}

		else
		{
			c = '*';
		}

		int i = 1;
		string line;
		while(getline(file, line))
		{
			fileData.resize(i);
			copy(line.begin(), line.end(), back_inserter(fileData[i-1]));
			++i;
		}

		// // Preprossing text chaging whitespaces with '?' for blocks and '*' for texts
		// for (int i = 0; i < fileData.size(); ++i)
		// {
		// 	for (int j = 0; j < fileData[0].size(); ++j)
		// 	{
		// 		if (fileData[i][j] == ' ')
		// 		{
		// 			fileData[i][j] = c;
		// 		}
		// 	}
		// }

		// // Print fileData
		// for (int i = 0; i < fileData.size(); ++i)
		// {
		// 	for (int j = 0; j < fileData[0].size(); ++j)
		// 	{
		// 		cout << fileData[i][j];
		// 	}

		// 	cout << endl;
		// }

		// cout << "File " << fileName << " was read successfully\n";
	}

	else
	{
		cout << "Failed to read file \"" << fileName << "\". The file doesn't exists! Please try again...\n\n";
		exit(EXIT_FAILURE);
	}
}

inline void
BlockAlignment::setTextSize()
{
	textSizeN = textData.size();
	textSizeM = textData[0].size();
	// cout << "Text size is " << textSizeN << "x" << textSizeM << endl;
}

inline void
BlockAlignment::setBlockSize()
{
	blockSizeN = blockData.size();
	blockSizeM = blockData[0].size();
	// cout << "Block size is " << blockSizeN << "x" << blockSizeM << endl;
}

inline void
BlockAlignment::getSequence(int n, int m)
{
	textSequence.clear();

	for (int i = n; i < blockSizeN + n; ++i)
	{
		for (int j = m; j < blockSizeM + m; ++j)
		{
			textSequence += textData[i][j];
		}
	}

	// This print all sequences with same size as block's
	// cout << textSequence << endl;
}

void
BlockAlignment::align()
{
	// Block
	readFile(blockFileName, blockData, blockSizeN, blockSizeM, 'b');
	setBlockSize();
	for (int i = 0; i < blockSizeN; ++i)
		for (int j = 0; j < blockSizeM; ++j)
			blockSequence += blockData[i][j];

	int k = 0;
	while (k < textFileNameList.size())
	{
		// Text
		textFileName = textFileNameList[k];
		// cout << "\nStarting alignment for " << textFileName << " and " << blockFileName << endl;
		readFile(textFileName, textData, textSizeN, textSizeM, 't');
		setTextSize();

		if (blockSizeN > textSizeN || blockSizeM > textSizeM)
		{
			cout << "Block \"" << blockFileName << "\" is bigger than text \"" << textFileName << "\". Please try again...\n\n";
			exit(EXIT_FAILURE);
		}

		alignment.clear();
		similarity.clear();

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

		// cout << "****************** alignment size: " << alignment.size() << "x" << alignment[0].size() << endl;
		// cout << "****************** similarity size: " << similarity.size() << "x" << similarity[0].size() << endl;

		// **************************************************************************************************** //

		int n = 0;
		int m = 0;
		sMax = INT_MIN;
		sIterator = 0;

		while (textSizeN - blockSizeN + 1 > n)
		{
			m = 0;
			while (textSizeM - blockSizeM + 1 > m)
			{
				getSequence(n, m);
				similarity[sIterator][1] = n;
				similarity[sIterator][2] = m;
				globalAlignment(textSequence, blockSequence);
				++m;
				++sIterator;
			}

			++n;
		}

		++k;
		print();
	}	
}

inline void
BlockAlignment::globalAlignment(string textSequence, string blockSequence)
{
	textSequenceResult.clear();
	blockSequenceResult.clear();

	int i, j, k;
	int n = textSequence.size() + 1;
	int m = blockSequence.size() + 1;

	// Construct alignment matrix
	for (k = 0; k < m; ++k)
	{
		alignment[0][k] = k * score('-', blockSequence[k]);
	}

	for (k = 0; k < n; ++k)
	{
		alignment[k][0] = k * score(textSequence[k], '-');
	}

	for (i = 1; i < n; ++i)
	{
		for (j = 1; j < m; ++j)
		{
			// if (blockSequence[j-1] == '?')
			// {
			// 	// alignment[i][j] = max(
			// 	// 	alignment[i-1][j] + score(textSequence[i-1], '-'),
			// 	// 	alignment[i][j-1] + score('-', blockSequence[j-1]),
			// 	// 	INT_MIN
			// 	// );

			// 	alignment[i][j] = alignment[i-1][j] + score(textSequence[i-1], '-');
				
			// 	// Do not increment j once it's inside a for loop
			// 	// ++j;
			// }

			// else
				alignment[i][j] = max(
					alignment[i-1][j] + score(textSequence[i-1], '-'),
					alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]),
					alignment[i][j-1] + score('-', blockSequence[j-1])
				);
		}
	}

	// for (i = 0; i < n; ++i)
	// {
	// 	for (j = 0; j < m; ++j)
	// 	{
	// 		cout << alignment[i][j] << "\t";
	// 	}

	// 	cout << endl;
	// }

	// cout << endl;

	// exit(1);
	// Problema deve estar na construção do alinhamento

	// Get similarity
	similarity[sIterator][0] = alignment[n-1][m-1];

	// Construct optimal alignment (result)
	i = textSequence.size();
	j = blockSequence.size();

	while (i != 0 && j != 0)
	{
		if (alignment[i][j] == alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]))
		{
			textSequenceResult += textSequence[i-1];
			blockSequenceResult += blockSequence[j-1];
			i--;
			j--;
		}

		else if (alignment[i][j] == alignment[i][j-1] + score('-', blockSequence[j-1]))
		{
			textSequenceResult += '-';
			blockSequenceResult += blockSequence[j-1];
			j--;
		}

		else if (alignment[i][j] == alignment[i-1][j] + score(textSequence[i-1], '-'))
		{
			textSequenceResult += textSequence[i-1];
			blockSequenceResult += '-';
			i--;
		}
	}

	while (i != 0)
	{
		textSequenceResult += textSequence[i-1];
		blockSequenceResult += '-';
		i--;
	}

	while (j != 0)
	{
		textSequenceResult += '-';
		blockSequenceResult += blockSequence[j-1];
		j--;
	}

	/**
	 * Revert results
	 * Here we use rbegin and rend to the string constructor to revert the string
	 */
	textSequenceResult = string(textSequenceResult.rbegin(), textSequenceResult.rend());
	blockSequenceResult = string(blockSequenceResult.rbegin(), blockSequenceResult.rend());

	// cout << textSequenceResult << endl;
	// cout << blockSequenceResult << endl;
	// cout << similarity[sIterator][0] << endl << endl;

	if (similarity[sIterator][0] > sMax)
	{
		sMax = similarity[sIterator][0];
		iMax = sIterator;
		bestResult[0] = textSequenceResult;
		bestResult[1] = blockSequenceResult;
	}
}

inline int
BlockAlignment::score(const char a, const char b)
{
	if 		(a == b)				return  1;
	else if (a != '-' && b != '-') 	return -1;
	else 							return -2;
}

inline int
BlockAlignment::max(int a, int b, int c)
{
	int max = a;
	(max < b) && (max = b);
	(max < c) && (max = c);
	return max;
}

inline void
BlockAlignment::print()
{
	// cout << "\nFinished alignment with " << numberOfSequences << " sequences" << endl;
	// cout << "S\tN\tM\n-----------------\n";
	// for (int i = 0; i < numberOfSequences; ++i)
	// cout << similarity[i][0] << "\t" << similarity[i][1] << "\t" << similarity[i][2] << endl;
	// cout << endl;

	cout << "\n> Best result and coordinate for files " << textFileName << " and " << blockFileName << endl;
	cout << "S\tN\tM\n-----------------\n";
	cout << similarity[iMax][0] << "\t" << similarity[iMax][1] << "\t" << similarity[iMax][2] << endl << endl;

	// Hits for ? chars
	int hits = 0;
	int j = 0;
	
	// Earn
	// char chars[] = "rost loss of setderricuriondi so of t notesilpoo wneton raostri ro si-";
	
	// Trade
	char chars[] = "aprn erly ly un int t haablxibanctt jes ra ily ";

	int sequenceSize = bestResult[0].size();

	for (int i = 0; i < sequenceSize; ++i)
	{
		if (bestResult[1][i] == '?')
		{
			if (bestResult[0][i] == chars[j])
			{
				++hits;
			}

			++j;
		}
	}

	double percent = ((double)hits / 47) * 100;

	cout << "Hits for ? chars: " << hits << " of 47" << endl;
	cout << "Hits percentage: ";
	cout << setprecision(3) << percent;
	cout << "%" << endl << endl;

	// cout << "> Text (best window)\n";
	// for (int i = similarity[iMax][1]; i < similarity[iMax][1] + blockSizeN; ++i)
	// {
	// 	for (int j = similarity[iMax][2]; j < similarity[iMax][2] + blockSizeM; ++j)
	// 	{
	// 		cout << textData[i][j];
	// 	}
	// 	cout << endl;
	// }
	
	// cout << "\n> Block (best window)\n";
	// for (int i = 0; i < blockSizeN; ++i)
	// {
	// 	for (int j = 0; j < blockSizeM; ++j)
	// 	{	
	// 		cout << blockData[i][j];
	// 	}
	// 	cout << endl;
	// }

	// Print best alignment
	// cout << "\n> Text (best alignment)" << endl << bestResult[0] << endl;
	// cout << "\n> Block (best alignment)" << endl << bestResult[1] << endl;


	cout << "> Best alignment for files " << textFileName << " and " << blockFileName << endl;
	
	#ifndef breakLine
	#define breakLine
	int breakLine = 150;
	#endif
	
	// for (int i = 0; i < sequenceSize; ++i)
	// {
		// Text sequence best result
		// cout << bestResult[0][i];
		// Block sequence best result
		// cout << bestResult[1][i];
	// }

	for (int i = 0; i < sequenceSize; i += breakLine)
	{
		int longerFileName = (int)textFileName.length();

		if ((int)blockFileName.length() > longerFileName)
		{
			longerFileName = (int)blockFileName.length();
			cout << textFileName << " ";
			for (int i = 0; i < (int)blockFileName.length() - (int)textFileName.length(); ++i)
			{
				cout << " ";
			}

			cout << bestResult[0].substr(i, breakLine) << endl;
		}

		else
			cout << textFileName << " " << bestResult[0].substr(i, breakLine) << endl;


		for (int j = 0; j < longerFileName + 1; ++j)
		{
			cout << " ";
		}

		for (int j = 0; j < (int)(bestResult[0].substr(i, breakLine)).length(); ++j)
		{
			if(bestResult[0][j+i] == bestResult[1][j+i])
				cout << "|";

			else if(bestResult[0][j+i] == '-' || bestResult[1][j+i] == '-')
				cout << " ";

			else
				cout << "!";
		}

		cout << endl;

		cout << blockFileName << " " << bestResult[1].substr(i, breakLine) << endl;
	}
}
