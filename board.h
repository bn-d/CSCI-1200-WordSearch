#ifndef __BOARD_H__
#define __BOARD_H__

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Board {
public:

  // Constructor
  Board(unsigned int r, unsigned int c) {
    board = vector<vector<char> >(r, vector<char>(c, '*'));
    dup = vector<vector<int> >(r, vector<int>(c, 0));
    empty = r * c;

  }

  // Accessors
  unsigned int numRows() const {
    return board.size();
  }

  unsigned int numColumns() const {
    return board[0].size();
  }

  char getChar(int r, int c) const {
    return board[r][c];
  }

  bool checkNoWord(const vector<string> &no_words) const {
    /*
    Return true if there no noWord. Return false otherwise
    */

    // Check each word
    for (unsigned int indx = 0; indx < no_words.size(); indx++) {
      // Check the current word
      int row_lim = this->numRows() - no_words[indx].size();
      int col_lim = this->numColumns() - no_words[indx].size();
      // Check horizontally
      for (unsigned int i = 0; i < this->numRows(); i++) {
        for (int j = 0; j <= col_lim; j++) {
          if (this->checkWord(i, j, no_words[indx], '4'))
            return false;
          if (this->checkWord(i, j, no_words[indx], '6'))
            return false;
        }
      }
      // Check vertically
      for (int i = 0; i <= row_lim; i++) {
        for (unsigned int j = 0; j < this->numColumns(); j++) {
          if (this->checkWord(i, j, no_words[indx], '8'))
            return false;
          if (this->checkWord(i, j, no_words[indx], '2'))
            return false;
        }
      }
      // Check diagonally
      for (int i = 0; i <= row_lim; i++) {
        for (int j = 0; j <= col_lim; j++) {
          if (this->checkWord(i, j, no_words[indx], '7'))
            return false;
          if (this->checkWord(i, j, no_words[indx], '3'))
            return false;
        }
      }
    }
    return true;
  }

  bool checkFilled() const {
    /*
    Check whether the board is completely filled
    */
    return empty == 0;
  }

  bool checkWord(int r, int c, string w, char dirc) const {
    /*
    Check whether a word is at given location with given roatation

    dirc: '4' horizontal      '6' horizontal reversed
          '8' vertical        '2' vertical reversed
          '7' diagonal        '3' diagonal reversed
    */

    // Prepare word and direction
    if (dirc == '6' || dirc == '2' || dirc == '3')
      reverse(w.begin(), w.end());

    int dx = 0; int dy = 0;
    if (dirc == '4' || dirc == '6' || dirc == '7' || dirc == '3')
      dx = 1;
    if (dirc == '8' || dirc == '2' || dirc == '7' || dirc == '3')
      dy = 1;

    // Check whether the move is legal
    for (unsigned int i = 0; i < w.size(); i++) {
      if (w[i] != board[r+i*dy][c+i*dx])
        return false;
    }
    return true;
  }

  // Modifiers
  bool setWord(int r, int c, string w, char dirc) {
    /*
    Check whether the word can be placed at given location with given roatation.
    Place the word and return true if the move is legal. Retrun false otherwise.
    */

    // Prepare word and direction
    if (dirc == '6' || dirc == '2' || dirc == '3')
      reverse(w.begin(), w.end());

    int dx = 0; int dy = 0;
    if (dirc == '4' || dirc == '6' || dirc == '7' || dirc == '3')
      dx = 1;
    if (dirc == '8' || dirc == '2' || dirc == '7' || dirc == '3')
      dy = 1;

    // Check whether the move is legal
    for (unsigned int i = 0; i < w.size(); i++) {
      if (w[i] != board[r+i*dy][c+i*dx] && board[r+i*dy][c+i*dx] != '*')
        return false;
    }

    // Set word to the board
    int empty_fill = 0;
    for (unsigned int i = 0; i < w.size(); i++) {
      board[r+i*dy][c+i*dx] = w[i];
      // Count the number of empty slots that get filled
      if (dup[r+i*dy][c+i*dx] == 0)
        empty_fill++;
      dup[r+i*dy][c+i*dx] += 1;
    }
    empty -= empty_fill;

    return true;
  }

  void delWord(int r, int c, unsigned int len, char dirc) {
    /*
    Delete word at given location with given roatation
    */

    // Prepare word and direction
    int dx = 0; int dy = 0;
    if (dirc == '4' || dirc == '6' || dirc == '7' || dirc == '3')
      dx = 1;
    if (dirc == '8' || dirc == '2' || dirc == '7' || dirc == '3')
      dy = 1;

    // Delete word from the board
    int empty_add = 0;
    for (unsigned int i = 0; i < len; i++) {
      // Count the number of slots that get emptied
      dup[r+i*dy][c+i*dx] -= 1;
      if (dup[r+i*dy][c+i*dx] == 0) {
        board[r+i*dy][c+i*dx] = '*';
        empty_add++;
      }
    }
    empty += empty_add;
  }

  // Printer
  void Print() const {
    cout << "Board:" << endl;
    for (unsigned int i = 0; i < this->numRows(); i++) {
      cout << "  ";
      for (unsigned int j = 0; j < this->numColumns(); j++)
        cout << board[i][j];
      cout << endl;
    }
  }

private:
  vector<vector<char> > board;
  vector<vector<int> > dup;
  int empty;

};


#endif
