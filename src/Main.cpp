#include "BlockAlignment.h"

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		BlockAlignment alignment;
		alignment.readFile(argv[1]);
	}

	else if (argc < 2)
	{
		cout << "Missing arguments! Please try again...\n\n";
		exit(EXIT_FAILURE);
	}

	else
	{
		cout << "Too many arguments! Please try again...\n\n";
		exit(EXIT_FAILURE);
	}

	return 0;
}
