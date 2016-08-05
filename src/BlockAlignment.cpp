#include "BlockAlignment.h"

void
BlockAlignment::readFile(const char *fileName,  vector<vector<char> > &fileData)
{
	// ifstream file(fileName, ios::in | ios::binary | ios::ate);
	ifstream file(fileName);

	if (file)
	{
		ifstream::pos_type fileSize = file.tellg();
		file.seekg(0, ios::beg);

		std::vector<char> data;

		int i = 1;
		string line;
		while(getline(file, line))
		{
			fileData.resize(i);
			copy(line.begin(), line.end(), back_inserter(fileData[i-1]));
			++i;
		}

		cout << fileName << " was read successfully!\n";
		// for (int i = 0; i < fileData.size(); ++i)
		// {
		// 	for (int j = 0; j < fileData[0].size(); ++j)
		// 	{
		// 		cout << fileData[i][j];
		// 	}

		// 	cout << endl;
		// }
		// cout << endl;
	}

	else
	{
		cout << "File \"" << fileName << "\" doesn't exists! Please try again...\n\n";
		exit(EXIT_FAILURE);
	}
}

void
BlockAlignment::setTextSize()
{
	textSizeN = textData.size();
	textSizeM = textData[0].size();
	// cout << "Text size is " << textSizeN << "x" << textSizeM << endl;
}

void
BlockAlignment::setBlockSize()
{
	blockSizeN = blockData.size();
	blockSizeM = blockData[0].size();
	// cout << "Block size is " << blockSizeN << "x" << blockSizeM << endl;
}

void
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
	int n = 0;
	int m = 0;
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
}

void
BlockAlignment::globalAlignment(string textSequence, string blockSequence)
{
	textSequenceResult.clear();
	blockSequenceResult.clear();

	int n = textSequence.size() + 1;
	int m = blockSequence.size() + 1;

	// Construct alignment matrix
	for (int k = 0; k < m; ++k)
	{
		alignment[0][k] = k * score('-', blockSequence[k]);
	}

	for (int k = 0; k < n; ++k)
	{
		alignment[k][0] = k * score(textSequence[k], '-');
	}

	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j)
		{
			alignment[i][j] = max(
				alignment[i-1][j] + score(textSequence[i-1], '-'),
				alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]),
				alignment[i][j-1] + score('-', blockSequence[j-1])
			);
		}
	}

	// Get similarity
	similarity[sIterator][0] = alignment[n-1][m-1];

	// Construct optimal alignment (result)
	int i = textSequence.size();
	int j = blockSequence.size();

	while(i != 0 && j != 0)
	{
		if(alignment[i][j] == alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]))
		{
			textSequenceResult += textSequence[i-1];
			blockSequenceResult += blockSequence[j-1];
			i--;
			j--;
		}

		else if(alignment[i][j] == alignment[i][j-1] + score('-', blockSequence[j-1]))
		{
			textSequenceResult += '-';
			blockSequenceResult += blockSequence[j-1];
			j--;
		}

		else if(alignment[i][j] == alignment[i-1][j] + score(textSequence[i-1], '-'))
		{
			textSequenceResult += textSequence[i-1];
			blockSequenceResult += '-';
			i--;
		}
	}

	while(i != 0)
	{
		textSequenceResult += textSequence[i-1];
		blockSequenceResult += '-';
		i--;
	}

	while(j != 0)
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
}

int
BlockAlignment::score(const char a, const char b)
{
	if (a == b) 					return 1;
	else if (a != '-' && b != '-') 	return -1;
	else 							return -2;
}

int
BlockAlignment::max(int a, int b, int c)
{
	int max = a;
	(max < b) && (max = b);
	(max < c) && (max = c);
	return max;
}

void
BlockAlignment::print()
{
	int i, max, maxI;

	cout << "Finished alignment with " << numberOfSequences << " sequences" << endl;
	cout << "S\tN\tM\n------------------\n";
	for (i = 0; i < numberOfSequences; ++i)
		cout << similarity[i][0] << "\t" << similarity[i][1] << "\t" << similarity[i][2] << endl;

	cout << endl;
	
	max = INT_MIN;
	for (i = 0; i < numberOfSequences; ++i)
		if (similarity[i][0] > max)
		{
			max = similarity[i][0];
			maxI = i;
		}

	cout << "Best result and cooridnate\n";
	cout << "S\tN\tM\n------------------\n";
	cout << similarity[maxI][0] << "\t" << similarity[maxI][1] << "\t" << similarity[maxI][2] << endl;
}