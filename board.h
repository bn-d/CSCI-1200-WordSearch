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
      // Do not rotate if it is a letter
      if (no_words[indx].size() == 1) {
        for (unsigned int i = 0; i < this->numRows(); i++) {
          for (unsigned int j = 0; j < this->numColumns(); j++)
            if (this->checkWord(i, j, no_words[indx], '4'))
              return false;
        }
      }
      else {
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
            if (this->checkWord(i, j, no_words[indx], '1'))
              return false;
            if (this->checkWord(i, j, no_words[indx], '9'))
              return false;
          }
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
    */

    // Prepare word and direction
    int dx = 0; int dy = 0;
    getDxDy(dirc, dx, dy, r, w);

    // Check whether the move is legal
    for (unsigned int i = 0; i < w.size(); i++) {
      if (w[i] != board[r+i*dy][c+i*dx])
        return false;
    }
    return true;
  }

  bool checkAvailable(int r, int c, string w, char dirc) {
    /*
      Check whether the move is legal
    */

    // Prepare word and direction
    int dx = 0; int dy = 0;
    getDxDy(dirc, dx, dy, r, w);

    // Check whether the move rewrite existing slots
    for (unsigned int i = 0; i < w.size(); i++) {
      if (w[i] != board[r+i*dy][c+i*dx] && board[r+i*dy][c+i*dx] != '*')
        return false;
    }
    return true;
  }

  // Modifiers
  void setWord(int r, int c, string w, char dirc) {
    /*
      Check whether the word can be placed at given location with given roatation.
      Place the word and return true if the move is legal. Retrun false otherwise.
    */

    // Prepare word and direction
    int dx = 0; int dy = 0;
    getDxDy(dirc, dx, dy, r, w);

    // Set word to the board
    int empty_fill = 0;
    for (unsigned int i = 0; i < w.size(); i++) {
      // Count the number of empty slots that get filled
      if (board[r+i*dy][c+i*dx] == '*') {
        empty_fill++;
        board[r+i*dy][c+i*dx] = w[i];
      }
    }
    empty -= empty_fill;
  }

  void fill_empty(char c) {
    for (unsigned int i = 0; i < this->numRows(); i++) {
      for (unsigned int j = 0; j < this->numColumns(); j++) {
        if (board[i][j] == '*') {
          board[i][j] = c;
          empty -= 1;
          return;
        }
      }
    }
  }

  // toString
  string toString(bool hori_filp=false, bool vert_flip=false) const {
    string ans = "";
    ans += "Board:\n";
    for (unsigned int i = 0; i < this->numRows(); i++) {
      ans += "  ";
      for (unsigned int j = 0; j < this->numColumns(); j++)
        if (!hori_filp && !vert_flip)
          ans += board[i][j];
        else if (hori_filp && !vert_flip)
          ans += board[i][this->numColumns()-1-j];
        else if (!hori_filp && vert_flip)
          ans += board[this->numRows()-1-i][j];
        else
          ans += board[this->numRows()-1-i][this->numColumns()-1-j];
      ans += "\n";
    }
    return ans;
  }

private:
  vector<vector<char> > board;
  int empty;

  void getDxDy(char dirc, int &dx, int &dy, int &r, string &w) const {
    /*
      Helper function for geting the value of dx, dy, w for given rotation


      dirc: '4' horizontal        '6' horizontal reversed
            '8' vertical          '2' vertical reversed
            '7' diagonal          '3' diagonal reversed
            '1' reversed diagonal '9' reversed diagonal reversed
    */

    if (dirc == '6' || dirc == '2' || dirc == '3' || dirc == '9')
      reverse(w.begin(), w.end());

    if (dirc == '4' || dirc == '6' || dirc == '7' || dirc == '3' || dirc == '1'
        || dirc == '9')
      dx = 1;
    if (dirc == '8' || dirc == '2' || dirc == '7' || dirc == '3')
      dy = 1;
    else if (dirc == '1' || dirc == '9')
      dy = -1;

    if (dirc == '1' || dirc == '9')
      r += w.size() - 1;
  }

};


#endif
