#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

// ==========================================================================
// Output the coreect usage
void usage(int argc, char *argv[]) {
  cerr << "USAGE: " << endl;
  cerr << "  " << argv[0] << " <input_filename> <output_filename> one_solution" << endl;
  cerr << "  " << argv[0] << " <input_filename> <output_filename> all_solutions" << endl;
  exit(1);
}

// ==========================================================================
// Parse the input arguments
void HandleCommandLineArguments(int argc, char *argv[], string &infile, string &outfile,
                                bool &all_solutions) {
  // Must have input and output file names
  if (argc < 3 || argc > 4) {
		cerr << "ERROR: unvalid number of arguments" << endl;
    usage(argc,argv);
  }
  infile = argv[1];
	outfile = argv[2];

	// Parse the solution options
  if (argc == 3 || argv[3] == string("one_solution")) {
		all_solutions = false;
	}
	else if (argv[3] == string("all_solutions")) {
		all_solutions = true;
	}
	else {
    cerr << "ERROR: unidentified solution option '" << argv[3] << "'" << endl;
    usage(argc,argv);
	}
}

// ==========================================================================
void ParseInputFile(const string &filename, int &row,
										int &col, vector<string> &words, vector<string> &no_words) {
  // Open the input file
  ifstream istr(filename.c_str());
  if (!istr) {
    cerr << "ERROR: cannot open input file '" << filename << "'" << endl;
    exit(1);
  }
  assert (istr);

  // Read each line of the input file
  string token, word;
	istr >> row >> col;
	// row = int(token);
	// col = int(word);
  while (istr >> token >> word) {
    if (token == "+")
    	words.push_back(word);
		else if (token == "-")
			no_words.push_back(word);
		else {
			cerr << "ERROR: unidentified token '" << token << "'" << endl;
			exit(1);
		}
  }
}

// ==========================================================================
int main(int argc, char *argv[]) {
	//==========Initialize variables
	string infile, outfile;
	int row = -1;
	int col = -1;
	bool all_solutions = false;
	vector<string> words, no_words;

	//==========Handle command line arguments and read file
	HandleCommandLineArguments(argc, argv, infile, outfile, all_solutions);
	ParseInputFile(infile, row, col, words, no_words);

	cout << row << " " << col << endl;
	for (unsigned int i = 0; i < words.size(); i++)
		cout << words[i] << endl;

	return 0;
}
