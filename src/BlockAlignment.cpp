#include "BlockAlignment.h"

void
BlockAlignment::readFile(char const *fileName)
{
	ifstream file(fileName);

	if (file)
	{
		string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		// const char *data = d.c_str();
		cout << "Input file name: " << fileName << endl << endl;
	}

	else
	{
		cout << "File doesn't exists! Please try again...\n\n";
		exit(EXIT_FAILURE);
	}
}
