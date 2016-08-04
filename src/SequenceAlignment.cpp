/**
 *
 * Author: Daniel de Faria Godoi
 * Subject: Introduction to Bioinformatics (Introdução à Bioinformática)
 * Title: Sequence Alignment (Alinhamento de Sequências)
 * Description: Compare two sequences with global, local or semiglobal alignment methods
 *
 * To compile, use
 * g++ *.cpp -Wall -pedantic -ansi
 * g++ -o SequenceAlignment SequenceAlignment.cpp -Wall -pedantic -ansi
 * 
 * Example to execute
 * ./a.out -g -u seq1.fasta -v seq2.fasta -i 2 -d 1 -e -2
 * ./SequenceAlignment -g -u seq1.fasta -v seq2.fasta -i 2 -d 1 -e -2
 *
 * Note: The file name may or may not have the extension, you choose!
 *
 */

#ifndef __SequenceAlignment_h
#define __SequenceAlignment_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

class SequenceAlignment
{
public:
	/**
	 *
	 * Default constructor for SequenceAlignment Class.
	 * It calls the parser method to read the entry.
	 *
	 */
	SequenceAlignment(int argc, char const *argv[])
	{
		parser(argc, argv);
	}

	/**
	 *
	 * Default destructor for SequenceAlignment Class.
	 * Vector C++ STL has its own destructor so no need to manually destruct it.
	 *
	 */
	~SequenceAlignment(){}

	// Auxiliary methods
	void parser(int, char const *[]);
	void readSequence(string&, string&, string&);
	int score(char, char);
	int max(int, int, int);
	void align();
	int getSimilarity();
	string getAlignmentType();

	// Algorithms
	void globalAlignment();
	void localAlignment();
	void semiglobalAlignment();

	// Print method to print the result
	void print();

	// Variables
	string alignmentType;
	string firstSequence;
	string secondSequence;
	string firstSequenceArchive;
	string secondSequenceArchive;
	string firstSequenceName;
	string secondSequenceName;
	string firstSequenceResult;
	string secondSequenceResult;
	int scoreEqual, scoreDiff, scoreSpace, similarity, n, m;

	// Multidimensional STL vector from <vector> library
	vector< vector<int> > M;
};

/**
 *
 * Parser method to read the entry and assign to each variable.
 * Here we use only one additional method (readSequence) to open file
 * and read the sequence name and the sequence.
 *
 */
void SequenceAlignment::parser(int argc, char const *argv[])
{
	// Verify if the user gave the 12 needed arguments
	if(argc == 12)
	{
		alignmentType = argv[1];
		firstSequenceArchive = argv[3];
		secondSequenceArchive = argv[5];

		readSequence(firstSequence, firstSequenceArchive, firstSequenceName);

		// Verify if the first file was read to read the second one
		if(firstSequence.size() != 0)
		{
			readSequence(secondSequence, secondSequenceArchive, secondSequenceName);

			// Verify if the second file was read to continue reading
			if(secondSequence.size() != 0)
			{
				// Build score
				scoreEqual = atoi(argv[7]);
				scoreDiff = atoi(argv[9]);
				scoreSpace = atoi(argv[11]);

				// Resize the vector with the length of first and second sequence
				n = firstSequence.size() + 1;
				m = secondSequence.size() + 1;
				M.resize(n);

				for (int i = 0; i < n; ++i)
				{
					M[i].resize(m);
				}
			}
		}	
	}

	else
		cout << "Input error: Missing arguments" << endl;
}

/**
 *
 * ReadSequence method to read a sequence.
 * This method opens a file and get the name and sequence from it.
 *
 */
void SequenceAlignment::readSequence(string &sequence, string &archive, string &name)
{
	// Open file
	ifstream file;
	file.open(archive.data());

	// First try (if the archive name has .fasta extension)
	if(file)
	{
		string line;

		// Get sequence name
		file >> name;
		name = name.substr(1);
		
		// Read the first line and do nothing (throw it away)
		getline(file, line);

		// Continue reading the file and add it to the string
		while(getline(file, line))
			sequence += line;

		// Close file
		file.close();
	}

	/**
	 * Second try (if the archive name don't have the .fasta extension).
	 * It actually concatenates ".fasta" to the archive name.
	 */
	else if(!file.is_open())
	{
		archive += ".fasta";
		file.open(archive.data());

		if(file)
		{
			string line;

			// Get sequence name
			file >> name;
			name = name.substr(1);
			
			// Read the first line and do nothing (throw it away)
			getline(file, line);

			// Continue reading the file and add it to the string
			while(getline(file, line))
				sequence += line;

			// Close file
			file.close();
		}
	}
	
	// Opening file error message
	else
	{
		cout << "Error opening file " << archive << ". Program aborted!" << endl;
	}
}

/**
 *
 * Score method to get the score.
 * This method receive two chars and return the score.
 *
 */
int SequenceAlignment::score(const char a, const char b)
{
	if(a == b)
		return scoreEqual;

	else if(a != '-' && b != '-')
		return scoreDiff;

	else
		return scoreSpace;
}

/**
 *
 * Max method to get max between three int values.
 * This method receives three int values and return the largest one.
 *
 */
int SequenceAlignment::max(int a, int b, int c)
{
	int max = a;

	// Boolean expressions to compare a, b and c
	(max < b) && (max = b);
	(max < c) && (max = c);

	return max;
}

/**
 *
 * Align method to align two sequences.
 * This method is used by main to call the correct alignment type.
 *
 */
void SequenceAlignment::align()
{
	if(getAlignmentType() == "-g")
		globalAlignment();

	else if(getAlignmentType() == "-s")
		semiglobalAlignment();

	else if(getAlignmentType() == "-l")
		localAlignment();

	else
		cout << "Input error: Wrong alignment type" << endl;
}

/**
 *
 * GetSimilarity method to get the similarity.
 * Returns the similarity.
 *
 */
int SequenceAlignment::getSimilarity()
{
	return similarity;
}

/**
 *
 * GetAlignmentType method to get the alignment type.
 * Returns the alignment type.
 *
 */
string SequenceAlignment::getAlignmentType()
{
	return alignmentType;
}

/**
 *
 * GlobalAlignment method to align two sequences.
 *
 */
void SequenceAlignment::globalAlignment()
{
	// Construct alignment matrix
	for (int k = 0; k < m; ++k)
	{
		M[0][k] = k * score('-', secondSequence[k]);
	}

	for (int k = 0; k < n; ++k)
	{
		M[k][0] = k * score(firstSequence[k], '-');
	}

	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j)
		{
			M[i][j] = max(
				M[i-1][j] + score(firstSequence[i-1], '-'),
				M[i-1][j-1] + score(firstSequence[i-1], secondSequence[j-1]),
				M[i][j-1] + score('-', secondSequence[j-1])
			);
		}
	}

	// Get similarity
	similarity = M[n-1][m-1];

	// Construct optimal alignment (result)
	int i = firstSequence.size();
	int j = secondSequence.size();

	while(i != 0 && j != 0)
	{
		if(M[i][j] == M[i-1][j-1] + score(firstSequence[i-1], secondSequence[j-1]))
		{
			firstSequenceResult += firstSequence[i-1];
			secondSequenceResult += secondSequence[j-1];
			i--;
			j--;
		}

		else if(M[i][j] == M[i][j-1] + score('-', secondSequence[j-1]))
		{
			firstSequenceResult += '-';
			secondSequenceResult += secondSequence[j-1];
			j--;
		}

		else if(M[i][j] == M[i-1][j] + score(firstSequence[i-1], '-'))
		{
			firstSequenceResult += firstSequence[i-1];
			secondSequenceResult += '-';
			i--;
		}
	}

	while(i != 0)
	{
		firstSequenceResult += firstSequence[i-1];
		secondSequenceResult += '-';
		i--;
	}

	while(j != 0)
	{
		firstSequenceResult += '-';
		secondSequenceResult += secondSequence[j-1];
		j--;
	}

	/**
	 * Revert results
	 * Here we use rbegin and rend to the string constructor to revert the string
	 */
	firstSequenceResult = string(firstSequenceResult.rbegin(), firstSequenceResult.rend());
	secondSequenceResult = string(secondSequenceResult.rbegin(), secondSequenceResult.rend());
}

/**
 *
 * LocalAlignment method to align two sequences.
 *
 */
void SequenceAlignment::localAlignment()
{
	/**
	 * Construct alignment matrix
	 * Here we use maxLocal to get the maximum value of the matrix
	 * and maxI and maxJ to get the position of this value
	 */
	int maxLocal = INT_MIN, 
		maxI = 0, 
		maxJ = 0;

	for (int k = 0; k < m; ++k)
	{
		M[0][k] = 0;
	}

	for (int k = 0; k < n; ++k)
	{
		M[k][0] = 0;
	}

	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j)
		{
			M[i][j] = max(
				M[i-1][j] + score(firstSequence[i-1], '-'),
				M[i-1][j-1] + score(firstSequence[i-1], secondSequence[j-1]),
				M[i][j-1] + score('-', secondSequence[j-1])
			);

			/**
			 * This condition is used because there's always an empty suffix alignment 
			 * from s[1...i] and t[1...j] with score equal zero
			 */
			if(M[i][j] < 0)
			{
				M[i][j] = 0;
			}

			// This condition is used to get the maximum value of the matrix
			if(M[i][j] > maxLocal)
			{
				maxLocal = M[i][j];
				maxI = i;
				maxJ = j;
			}
		}
	}

	// Get similarity
	similarity = maxLocal;

	// Construct optimal alignment (result)
	int i = maxI;
	int j = maxJ;

	while(M[i][j] != 0)
	{
		if(M[i][j] == M[i-1][j-1] + score(firstSequence[i-1], secondSequence[j-1]))
		{
			firstSequenceResult += firstSequence[i-1];
			secondSequenceResult += secondSequence[j-1];
			i--;
			j--;
		}

		else if(M[i][j] == M[i][j-1] + score('-', secondSequence[j-1]))
		{
			firstSequenceResult += '-';
			secondSequenceResult += secondSequence[j-1];
			j--;
		}

		else if(M[i][j] == M[i-1][j] + score(firstSequence[i-1], '-'))
		{
			firstSequenceResult += firstSequence[i-1];
			secondSequenceResult += '-';
			i--;
		}
	}

	/**
	 * Revert results
	 * Here we use rbegin and rend to the string constructor to revert the string
	 */
	firstSequenceResult = string(firstSequenceResult.rbegin(), firstSequenceResult.rend());
	secondSequenceResult = string(secondSequenceResult.rbegin(), secondSequenceResult.rend());
}

/**
 *
 * SemiglobalAlignment method to align two sequences.
 *
 */
void SequenceAlignment::semiglobalAlignment()
{
	/**
	 * Construct alignment matrix
	 * Here we use maxLocal to get the maximum value of the last row or column of the matrix
	 * and maxI and maxJ to get the position of this value
	 */
	int maxLocal = INT_MIN,
		maxI = 0,
		maxJ = m-1;

	for (int k = 0; k < m; ++k)
	{
		M[0][k] = 0;
	}

	for (int k = 0; k < n; ++k)
	{
		M[k][0] = 0;
	}

	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j)
		{
			M[i][j] = max(
				M[i-1][j] + score(firstSequence[i-1], '-'),
				M[i-1][j-1] + score(firstSequence[i-1], secondSequence[j-1]),
				M[i][j-1] + score('-', secondSequence[j-1])
			);
		}
	}

	// Get maximum value of last raw or column (similarity)
	for (int i = 1; i < n; ++i)
	{
		if(M[i][m-1] > maxLocal)
		{
			maxLocal = M[i][m-1];
			maxI = i;
		}
	}

	for (int j = 0; j < m-1; ++j)
	{
		if(M[n-1][j] > maxLocal)
		{
			maxLocal = M[n-1][j];
			maxI = n-1;
			maxJ = j;
		}
	}

	// Get similarity
	similarity = maxLocal;

	// Construct optimal alignment (result)
	int i = maxI;
	int j = maxJ;

	for (int k = n-1; k > maxI; --k)
	{
		firstSequenceResult += firstSequence[k-1];
		secondSequenceResult += '-';
	}

	for (int k = m-1; k > maxJ; --k)
	{
		firstSequenceResult += '-';
		secondSequenceResult += secondSequence[k-1];
	}

	while(i != 0 && j != 0)
	{
		if(M[i][j] == M[i-1][j-1] + score(firstSequence[i-1], secondSequence[j-1]))
		{
			firstSequenceResult += firstSequence[i-1];
			secondSequenceResult += secondSequence[j-1];
			i--;
			j--;
		}

		else if(M[i][j] == M[i][j-1] + score('-', secondSequence[j-1]))
		{
			firstSequenceResult += '-';
			secondSequenceResult += secondSequence[j-1];
			j--;
		}

		else if(M[i][j] == M[i-1][j] + score(firstSequence[i-1], '-'))
		{
			firstSequenceResult += firstSequence[i-1];
			secondSequenceResult += '-';
			i--;
		}
	}

	while(i != 0)
	{
		firstSequenceResult += firstSequence[i-1];
		secondSequenceResult += '-';
		i--;
	}

	while(j != 0)
	{
		firstSequenceResult += '-';
		secondSequenceResult += secondSequence[j-1];
		j--;
	}

	/**
	 * Revert results
	 * Here we use rbegin and rend to the string constructor to revert the string
	 */
	firstSequenceResult = string(firstSequenceResult.rbegin(), firstSequenceResult.rend());
	secondSequenceResult = string(secondSequenceResult.rbegin(), secondSequenceResult.rend());
}

/**
 *
 * Print method to print the aligned sequences and the similarity.
 *
 */
void SequenceAlignment::print()
{
	int sequenceResultSize = firstSequenceResult.length();

	for (int i = 0; i < sequenceResultSize; i += 30)
	{
		cout << firstSequenceName << " " << firstSequenceResult.substr(i, 30) << endl;

		for (int j = 0; j <= (int)firstSequenceName.length(); ++j)
		{
			cout << " ";
		}

		for (int j = 0; j < (int)(firstSequenceResult.substr(i, 30)).length(); ++j)
		{
			if(firstSequenceResult[j+i] == secondSequenceResult[j+i])
				cout << "|";

			else if(firstSequenceResult[j+i] == '-' || secondSequenceResult[j+i] == '-')
				cout << " ";

			else
				cout << "!";
		}

		cout << endl;

		cout << secondSequenceName << " " << secondSequenceResult.substr(i, 30) << endl;
	}

	cout << "similaridade: " << getSimilarity() << endl;
}

///**
// *
// * Main method to call the SequenceAlignment methods.
// *
// */
//int main(int argc, char const *argv[])
//{
//	// Create a new object of SequenceAlignment class using argc and argv as arguments
//	SequenceAlignment *alignment = new SequenceAlignment(argc, argv);
//
//	// Align method that align the sequences
//	alignment->align();
//
//	// Print method that print the aligned sequences and the similarity
//	alignment->print();
//
//	return 0;
//}

#endif