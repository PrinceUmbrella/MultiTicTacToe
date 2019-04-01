#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <string>



class Board{
  
  private:

  int board_row;
  int board_column;
  char** board;

  public:

  Board(int row_size, int col_size );
  ~Board();
  int getRow();
  int getColumn();
  char** getBoard();
  char** initializeBoard();
  void printBoard();
  void make_Move(int user_Row_Choice, int user_Column_Choice, char user_char);
  bool checkWin(char userChoice);

};


#endif // BOARD_H
