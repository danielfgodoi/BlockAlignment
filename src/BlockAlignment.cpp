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
			i++;
		}

		cout << fileName << " was read successfully!\n";
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
	textSizeN = text.size();
	textSizeM = text[0].size();
	cout << "Text size is " << textSizeN << "x" << textSizeM << endl;
}

void
BlockAlignment::setBlockSize()
{
	blockSizeN = block.size();
	blockSizeM = block[0].size();
	cout << "Block size is " << blockSizeN << "x" << blockSizeM << endl;
}

void
BlockAlignment::parse()
{
	
}

void
BlockAlignment::align()
{
	parse();
}