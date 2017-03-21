#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>


class Board {
public:

  // Constructor
  Board(int i, int j) {

  }

  // Accessors
  int numRows() const { return board.size(); }
  int numColumns() const { return board[0].size(); }
  Tile* getTile(int i, int j) const;
  void begin_end(int &r_beg, int &r_end, int &c_beg, int &c_end) const;

  // MODIFIERS
  void setTile(int i, int j, Tile* t);
  void setNULL(int i, int j);

  // FOR PRINTING
  void Print() const;
  void PrintSmall() const;

private:

  std::vector<std::vector<char> > board;
};


#endif
