#include "BlockAlignment.h"

int main(int argc, char const *argv[])
{
	if (argc > 5)
	{
		cout << "Missing arguments! Please try again...\n";
		cout << "To execute run bin/BlockAlignment -t <text files list> -b <block file>\n\n";
		exit(EXIT_FAILURE);	
	}

	else
	{
		BlockAlignment blockAlignment(argc, argv);
		// blockAlignment.parse();
		blockAlignment.align();
		blockAlignment.print();
	}

	return 0;
}
