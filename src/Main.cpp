#include "BlockAlignment.h"

int main(int argc, char const *argv[])
{
	string fileType;
	string blockFileName;
	vector<string> textFileNameList;

	if (argc < 5)
	{
		cout << "Missing arguments! Please try again...\n";
		cout << "To execute run bin/BlockAlignment -t <text files list> -b <block file>\n\n";
		exit(EXIT_FAILURE);
	}


	else
	{
		fileType = argv[1];

		// bin/BlockAlignment -t test/text test/text test/text -b test/block

		if (fileType == "-t")
		{
			int i = 2;
			while (i < 5)
			{
				cout << argv[i] << " - ";
				textFileNameList.push_back(argv[i]);
				++i;
			}

			cout << endl << endl;
			// blockFileName = argv[i+2];
		}

		else if (fileType == "-b")
		{
			blockFileName = argv[2];
			
			int i = 3;
			while (i < argc)
			{
				// textFileNameList.push_back(argv[i]);
				++i;
			}
		}
				
		else
		{
			cout << "Invalid argument " << argv[1] << "! Please try again...\n\n";
			exit(EXIT_FAILURE);			
		}

		cout << "blockFileName: " << blockFileName << endl;

		cout << "textFileNameList: ";
		for (int i = 0; i < textFileNameList.size(); ++i)
			cout << textFileNameList[i] << " - ";

		cout << endl << endl;

		BlockAlignment blockAlignment(argc, argv);
		// blockAlignment.parse();
		blockAlignment.align();
		blockAlignment.print();
	}

	return 0;
}
