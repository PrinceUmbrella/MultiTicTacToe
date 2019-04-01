#include "Board.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
struct Player{
    string firstName;
    string fullName;
    int gamesWon;
    int gameLoss;
    int gameDrawn;

    char piece;
};

/*////////////////////////////////////////////////////////////////

    Get the row and column sizes
    Initialize the board and the size

//////////////////////////////////////////////////////////////////*/

Board::Board(int row_size , int col_size) {

    board_row = row_size;
    board_column = col_size;

    board = initializeBoard();

}

/*////////////////////////////////////////////////////////////////

    Clear the memory by the board

//////////////////////////////////////////////////////////////////*/
Board::~Board(){
    for (int i = 0; i < board_row; ++i) {

        delete [] board[i];
    }
    delete [] board;
}
/*////////////////////////////////////////////////////////////////

    Return the row size

//////////////////////////////////////////////////////////////////*/

int Board::getRow(){

    return board_row;
}

/*////////////////////////////////////////////////////////////////

    Return the column size

//////////////////////////////////////////////////////////////////*/

int Board::getColumn(){

    return board_column;
}

/*////////////////////////////////////////////////////////////////

    Return the board pointer

//////////////////////////////////////////////////////////////////*/

char** Board::getBoard(){

    return board;
}

/*////////////////////////////////////////////////////////////////

    Dynamically allocate the memory for the board
    return the pointer to that array

//////////////////////////////////////////////////////////////////*/

char **Board::initializeBoard () {

    char** playing_board;
    playing_board = nullptr;
    playing_board = new char*[board_row];

    for (int row = 0; row < board_row ; row++ ) {

        playing_board[row] = nullptr;
        playing_board[row] = new char[board_column];

    }

    char location = ' ';
    for (int row = 0 ; row < board_row; row++ ) {

        for( int column = 0; column < board_column; column++ ) {

            playing_board[row][column] = location;
        }
    }
    return playing_board;
}

/*////////////////////////////////////////////////////////////////

    Print the board

//////////////////////////////////////////////////////////////////*/

void Board::printBoard() {

    int column_choice = 1;
    char row_choice = 'A';

    cout <<endl;
    cout<< "  " << setw(2);

    for (int column = 0; column < board_column; column++ ){

        cout << setw(4) << column_choice << setw(2);
        column_choice++;
    }

    cout << endl ;
    cout << setw(4) << " " ;

    for (int column = 0; column < board_column; column++ ){

            cout<< setw(2)<< "--- "<< setw(2);
        }

    cout<<"\n";

    row_choice = 'A';
    for (int row = 0; row < board_row; row++ ){

        cout<< setw(2) << row_choice << setw(2) << "|";

        for (int column = 0; column < board_column; column++ ){

            cout<< setw(2)<<board[row][column]<< setw(2) << "|" ;
        }

        cout<< setw(2)<< row_choice<< setw(2);
        cout<<"\n";
        cout<< setw(4)<<" ";

        for (int column = 0; column < board_column; column++){
            cout<< setw(2)<< "--- "<< setw(2) ;
        }
        row_choice++;

        cout << "\n";
    }
    column_choice = 1;
    cout<< "  " << setw(2);
    for (int column = 0; column < board_column; column++){

        cout<< setw(4)<<column_choice<< setw(2);
        column_choice++;
    }
    cout<< endl;

}

/*////////////////////////////////////////////////////////////////

    Get the move Row and Column and replace the position with the
    users characters

//////////////////////////////////////////////////////////////////*/

void Board::make_Move(int user_Row_Choice, int user_Column_Choice, char user_char ){

    board[user_Row_Choice][user_Column_Choice] = user_char;

}

/*////////////////////////////////////////////////////////////////////

    Check if there is a win and return a TRUE if there is any matching
    Case

/////////////////////////////////////////////////////////////////////*/

bool Board::checkWin(char userChoice){
    bool gameOverVal;
    int Upper_Lower_difference = 32;
    gameOverVal =false;

    for (int row = 0; row < board_row && !gameOverVal; row++){

        for (int column = 0; column < board_column - 2 && !gameOverVal; column++){

            if (board[row][column] == userChoice &&
                board[row][column+1] == userChoice &&
                board[row][column+2] == userChoice){

                    board[row][column] = userChoice - Upper_Lower_difference;
                    board[row][column + 1] = userChoice - Upper_Lower_difference;
                    board[row][column + 2] = userChoice - Upper_Lower_difference;
                    gameOverVal = true;
            }
        }
    }

    for (int row = 0; row < board_row - 2 && !gameOverVal; row++){

        for (int column = 0; column < board_column && !gameOverVal; column++){

            if (board[row][column] == userChoice &&
                board[row + 1][column] == userChoice &&
                board[row + 2][column] == userChoice){

                    board[row][column] = userChoice - Upper_Lower_difference;
                    board[row + 1][column] = userChoice - Upper_Lower_difference;
                    board[row + 2][column] = userChoice - Upper_Lower_difference;
                    gameOverVal = true;

            }
        }
    }

    for (int row = 0; row < board_row - 2; row++){

        for (int column = 0; column < board_column - 2; column++){

            if (board[row][column] == userChoice &&
                board[row + 1][column + 1] == userChoice &&
                board[row + 2][column + 2] == userChoice){

                    board[row][column] = userChoice - Upper_Lower_difference;
                    board[row + 1][column + 1] = userChoice - Upper_Lower_difference;
                    board[row + 2][column + 2] = userChoice - Upper_Lower_difference;
                    gameOverVal = true;
            }
        }

    }
    for (int row = 0; row < board_row - 2; row++){

        for (int column = board_column - 1; column > 1; column--){

            if (board[row][column] == userChoice &&
                board[row + 1][column - 1] == userChoice &&
                board[row + 2][column - 2] == userChoice){

                    board[row][column] = userChoice - Upper_Lower_difference;
                    board[row + 1][column - 1] = userChoice - Upper_Lower_difference;
                    board[row + 2][column - 2] = userChoice - Upper_Lower_difference;
                    gameOverVal = true;
            }
        }
    }
    return gameOverVal;
}





