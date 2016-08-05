#include "BlockAlignment.h"

int main(int argc, char const *argv[])
{
	if (argc == 3)
	{
		BlockAlignment blockAlignment(argv[1], argv[2]);
		// blockAlignment.align();
		// blockAlignment.print();
	}

	else if (argc < 3)
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
