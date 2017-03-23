#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <set>
#include <string>
#include <vector>

#include "board.h"

using namespace std;

// Declaration
bool compareLen(const string &a, const string &b);
void wordSearch(Board b, vector<Board> &ans, const vector<string> &words,
                const vector<string> &no_words, const bool &all_solutions);
void word_recur(Board b, vector<Board> &ans, const vector<string> &words,
                const vector<string> &no_words, const bool &all_solutions, int r,
                int c, char dirc, unsigned int indx);
void word_empty_fill(Board b, vector<Board> &ans, const vector<string> &no_words,
                    char fill_char);

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
void HandleCommandLineArguments(int argc, char *argv[], string &infile,
                                bool &all_solutions) {
  // Must have input and output file names
  if (argc < 2 || argc > 3) {
		cerr << "ERROR: unvalid number of arguments" << endl;
    usage(argc,argv);
  }
  infile = argv[1];

	// Parse the solution options
  if (argc == 2 || argv[2] == string("one_solution")) {
		all_solutions = false;
	}
	else if (argv[2] == string("all_solutions")) {
		all_solutions = true;
	}
	else {
    cerr << "ERROR: unidentified solution option '" << argv[3] << "'" << endl;
    usage(argc,argv);
	}
}

// ==========================================================================
void ParseInputFile(const string &filename, unsigned int &col,
										unsigned int &row, vector<string> &words, vector<string> &no_words) {
  // Open the input file
  ifstream istr(filename.c_str());
  if (!istr) {
    cerr << "ERROR: cannot open input file '" << filename << "'" << endl;
    exit(1);
  }
  assert (istr);

  // Read each line of the input file
  string token, word;
	istr >> col >> row;
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
	// Initialize variables
	string infile;
	unsigned int row = 0;
	unsigned int col = 0;
	bool all_solutions = false;
	vector<string> words, no_words;

	// Handle command line arguments and read file
	HandleCommandLineArguments(argc, argv, infile, all_solutions);
	ParseInputFile(infile, col, row, words, no_words);

  // Creat Board
	Board b = Board(row, col);
  vector<Board> ans = vector<Board>();

  // Sort words and no_words by string lengght
  sort(words.begin(), words.end(), compareLen);
  sort(no_words.begin(), no_words.end(), compareLen);
  reverse(no_words.begin(), no_words.end());

  // Start recursion
  wordSearch(b, ans, words, no_words, all_solutions);

  // Find variant solutions for unique solutions
  set<string> ans_set = set<string>();
  for (unsigned int i = 0; i < ans.size(); i++) {
    ans_set.insert(ans[i].toString());
    ans_set.insert(ans[i].toString(true, false));
    ans_set.insert(ans[i].toString(false, true));
    ans_set.insert(ans[i].toString(true, true));
  }

  for (set<string>::iterator it=ans_set.begin(); it != ans_set.end(); it++) {
    cout << *it;
  }

  // Print solution(s)
  if (ans_set.size() == 0)
    cout << endl << "No solution" << endl;
  else
    cout << endl << "Found " << ans_set.size() << " solution(s)" << endl;

	return 0;
}

// ==========================================================================
bool compareLen(const string &a, const string &b) {
  /*
    Compare two string by length
  */
  return a.size() > b.size();
}

// ==========================================================================
void wordSearch(Board b, vector<Board> &ans, const vector<string> &words,
                const vector<string> &no_words, const bool &all_solutions) {
  /*
    Prepare for first layer of recursion
  */

  // Place the first word at upper left corner
  int row_lim = (b.numRows() - words[0].size()) / 2;
  int col_lim = (b.numColumns() - words[0].size()) / 2;
  // Place horizontally
  if (words[0].size() == b.numColumns()) {
    for (unsigned int i = 0; i < ceil(b.numRows() / 2.); i++){
      if (b.checkAvailable(i, 0, words[0], '4'))
        word_recur(b, ans, words, no_words, all_solutions, i, 0, '4', 0);
    }
  }
  else {
    for (unsigned int i = 0; i < ceil(b.numRows() / 2.); i++) {
      for (int j = 0; j <= col_lim; j++) {
        if (b.checkAvailable(i, j, words[0], '4'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '4', 0);
        if (b.checkAvailable(i, j, words[0], '6'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '6', 0);
      }
    }
  }

  // Place vertically
  if (words[0].size() == b.numRows()) {
      for (unsigned int j = 0; j < ceil(b.numColumns() / 2.); j++) {
        if (b.checkAvailable(0, j, words[0], '8'))
          word_recur(b, ans, words, no_words, all_solutions, 0, j, '8', 0);      }
  }
  else {
    for (int i = 0; i <= row_lim; i++) {
      for (unsigned int j = 0; j < ceil(b.numColumns() / 2.); j++) {
        if (b.checkAvailable(i, j, words[0], '8'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '8', 0);
        if (b.checkAvailable(i, j, words[0], '2'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '2', 0);
      }
    }
  }
  // Place diagonally
  if (words[0].size() == b.numRows() || words[0].size() == b.numColumns()) {
    for (int i = 0; i <= row_lim; i++) {
      for (int j = 0; j <= col_lim; j++) {
        if (b.checkAvailable(i, j, words[0], '7'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '7', 0);
        if (b.checkAvailable(i, j, words[0], '3'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '3', 0);
      }
    }
  }
  else {
    for (int i = 0; i <= row_lim; i++) {
      for (int j = 0; j <= col_lim; j++) {
          if (b.checkAvailable(i, j, words[0], '7'))
            word_recur(b, ans, words, no_words, all_solutions, i, j, '7', 0);
          if (b.checkAvailable(i, j, words[0], '3'))
            word_recur(b, ans, words, no_words, all_solutions, i, j, '3', 0);
          if (b.checkAvailable(i, j, words[0], '1'))
            word_recur(b, ans, words, no_words, all_solutions, i, j, '1', 0);
          if (b.checkAvailable(i, j, words[0], '9'))
            word_recur(b, ans, words, no_words, all_solutions, i, j, '9', 0);
      }
    }
  }
}

// ==========================================================================
void word_recur(Board b, vector<Board> &ans, const vector<string> &words,
                const vector<string> &no_words, const bool &all_solutions, int r,
                int c, char dirc, unsigned int indx) {
  /*
    Add word to board recursively
  */

  // Add word
  b.setWord(r, c, words[indx], dirc);

  if (b.checkNoWord(no_words)) {
    indx++;
    // If added all words
    if (indx == words.size()) {
      // Add finished board to answer list for all solution
      if (b.checkFilled()) {
        // Stop searching after one solution if not all solutions
        if (!all_solutions) {
          cout << b.toString();
          exit(0);
        }
        ans.push_back(b);
      }
      // Fill unfilled board
      else {
        for (char c = 'a'; c <= 'z'; c++)
          word_empty_fill(b, ans, no_words, c);
      }
      return;
    }

    // Place the current word
    int row_lim = b.numRows() - words[indx].size();
    int col_lim = b.numColumns() - words[indx].size();
    // Place horizontally
    for (unsigned int i = 0; i < b.numRows(); i++) {
      for (int j = 0; j <= col_lim; j++) {
        if (b.checkAvailable(i, j, words[indx], '4'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '4', indx);
        if (b.checkAvailable(i, j, words[indx], '6'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '6', indx);
      }
    }
    // Place vertically
    for (int i = 0; i <= row_lim; i++) {
      for (unsigned int j = 0; j < b.numColumns(); j++) {
        if (b.checkAvailable(i, j, words[indx], '8'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '8', indx);
        if (b.checkAvailable(i, j, words[indx], '2'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '2', indx);
      }
    }
    // Place diagonally
    for (int i = 0; i <= row_lim; i++) {
      for (int j = 0; j <= col_lim; j++) {
        if (b.checkAvailable(i, j, words[indx], '7'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '7', indx);
        if (b.checkAvailable(i, j, words[indx], '3'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '3', indx);
        if (b.checkAvailable(i, j, words[indx], '1'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '1', indx);
        if (b.checkAvailable(i, j, words[indx], '9'))
          word_recur(b, ans, words, no_words, all_solutions, i, j, '9', indx);
      }
    }
  }
}

// ==========================================================================
void word_empty_fill(Board b, vector<Board> &ans, const vector<string> &no_words,
                      char fill_char) {
  /*
    Fill the left empty slot recursively
  */

  // Fill a slots
  b.fill_empty(fill_char);

  if (b.checkNoWord(no_words)) {
    if (b.checkFilled())
      ans.push_back(b);
    else {
      for (char c = 'a'; c <= 'z'; c++)
        word_empty_fill(b, ans, no_words, c);
    }
  }
}
