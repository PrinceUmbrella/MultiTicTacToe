#include <iostream>
#include <iomanip>
#include <string>
#include "Board.h"

/*////////////////////////////////////////////////////////////////////
Name: Leoul Tilahun
MId: M00082868
Date: 02/11/2019
To: Dr Ng
//////////////////////////////////////////////////////////////////////*/

using namespace std;

/*////////////////////////////////////////////////////////////

                        CONSTANTS

///////////////////////////////////////////////////////////*/

const int MAX_ROW_SIZE = 11;
const int MAX_COL_SIZE = 14;
const int MIN_ROW_SIZE = 3;
const int MIN_COL_SIZE = 3;
const int MAX_NUMBER_PLAYERS = 5;
const int MIN_NUMBER_PLAYERS = 2;

/*////////////////////////////////////////////////////////////

                PLAYER STRUCT

///////////////////////////////////////////////////////////*/

struct Player{

    string firstName;
    string fullName;
    int gamesWon;
    int gamesLoss;
    int gamesDrawn;
    char piece;

};

/*////////////////////////////////////////////////////////////

            Prototypes

///////////////////////////////////////////////////////////*/

int getNumberOfPlayer();
void openningStatement();
char toUpper(char letter);
char toLower(char letter);
string getName(int player_number);
string getFirstName(string userName);
bool checkNoLastName(string userName);
string changeToCapital(string userName);
bool check_Characters(string user_Name);
string remove_spaces(string Player_name);
string toLowerCaseString(string user_Name);
Player* create_Players(int numberOfPlayers);
int getSize(const int MAX_SIZE, char rowOrCol);
void printStat(Player* gamePlayers, int numberOfPlayers);
int* checkUserMoves(string userInput, Board& playingBoard);
void get_UserMove(Player currentPlayer, Board& playingBoard);
void update_Status(Player* gamePlayers, int turn, int numberOfPlayers);
int* checkUserPosition(int* playerMove, Board& playingBoard, Player currentPlayer);



int main(){

    Player* gamePlayers;
    int numberOfPlayers, totalGames;
    int currentPlayer, turn, numberOfMoves;
    int row, column;
    bool gameWon;
    string quit = "0";

    openningStatement();

    numberOfPlayers = getNumberOfPlayer();
    gamePlayers   = create_Players(numberOfPlayers);


    for (int i = 0; i < numberOfPlayers; i++){

        gamePlayers[i].fullName  = getName(i);

        gamePlayers[i].firstName = getFirstName(gamePlayers[i].fullName);
    }

    currentPlayer = 0;
    gameWon = false;
    totalGames = 0;


    do{

        cout<<endl<< " Please enter the dimension of the board: "<< endl;
        turn = currentPlayer;
        row = getSize(MAX_ROW_SIZE, 'r');
        column = getSize(MAX_COL_SIZE, 'c');
        Board playingBoard(row, column);
        numberOfMoves = 0;
        gameWon = false;

        do{
            playingBoard.printBoard();
            get_UserMove(gamePlayers[turn], playingBoard);
            numberOfMoves++;

            if (playingBoard.checkWin(gamePlayers[turn].piece)){
                gameWon = true;
            }
            else{
                if (numberOfMoves < row * column){
                    turn = (turn + 1) % numberOfPlayers;
                }
            }

        }while ((!gameWon) && (numberOfMoves < row * column));

        totalGames++;

        if (gameWon){
            update_Status(gamePlayers, turn, numberOfPlayers);
            playingBoard.printBoard();
            cout<< " Congratulations "<<  gamePlayers[turn].fullName<< " You won the game!!! "<< endl;
            currentPlayer = (turn + 1) % numberOfPlayers;
        }

        if (!gameWon && numberOfMoves == row * column){

            update_Status(gamePlayers, numberOfPlayers, numberOfPlayers);
            playingBoard.printBoard();
            cout<< endl<<"The Game has ended in a Draw!!!"<< endl;
            currentPlayer = (currentPlayer + 1) % numberOfPlayers;
        }


        cout<<endl<< "Total game(s) played = "<< totalGames<< "\n\n";
        printStat(gamePlayers, numberOfPlayers);

        cout<<endl<< " If you want to quit hit only \"0\" (zero) else hit any character"<< endl;
        cout<< " Do you want to quit? ";
        getline(cin, quit);

    }while(quit != "0");

}
/*////////////////////////////////////////////////////////////

    - gets a character and returns the smaller version
    of letter

///////////////////////////////////////////////////////////*/

char toLower(char letter){
    char lowerCase;
    if (letter >= 'A' && letter <= 'Z'){
        lowerCase = letter + 32;
        return lowerCase;
    }
    else{
        return letter;
    }
}

/*////////////////////////////////////////////////////////////

    - gets a character and returns the Capitalized version
    of letter

///////////////////////////////////////////////////////////*/

char toUpper(char letter){
    char upperCase;
    if (letter >= 'a' && letter <= 'z'){
        upperCase = letter - 32;
        return upperCase;
    }
    else{
        return letter;
    }
}

/*////////////////////////////////////////////////////////////////

    Get the player and the Board
    - get the position Input form the user
    - Verify the input
    - Call the method to make the move

//////////////////////////////////////////////////////////////////*/

void get_UserMove(Player currentPlayer, Board& playingBoard){

    string userInput;
    int* playerMove;
    int row_Move;
    int column_Move;

    cout<< " "<<currentPlayer.firstName<< "'s move("<< currentPlayer.piece<< ") Please choose a Move ---> ";
    getline(cin, userInput);

    playerMove = checkUserMoves(userInput, playingBoard);
    playerMove = checkUserPosition(playerMove, playingBoard,currentPlayer);

    row_Move = playerMove[0];
    column_Move = playerMove[1];

    playingBoard.make_Move(row_Move,column_Move, currentPlayer.piece);

}

/*///////////////////////////////////////////////////////////////////////

    Get the user Move and the Board
    - check whether if the input is in a correct form
        - check if it has length b/n 2-3
        - check the letter input
        - check the number
    - change the final input to LETTER NUMBER FORM
    Return an array which contains the {row position, column position}

///////////////////////////////////////////////////////////////////////*/

int* checkUserMoves(string userInput, Board& playingBoard){

    int* userMoves = nullptr;
    char rowMove;
    char maxRow;
    bool incorrectInput;
    userMoves = new int[2];


    maxRow = 'a' + (playingBoard.getRow() - 1);
    incorrectInput = false;

    while (!incorrectInput){

        if (userInput.length() < 2 || userInput.length() > 3){

            incorrectInput = true;
        }

        rowMove = toLower(userInput[0]);
        if (rowMove < 'a' || rowMove > maxRow){

            incorrectInput = true;
        }

        if (userInput[1] < '1' || userInput[1] > '9'){

            incorrectInput = true;
        }

        if (userInput.length() == 3){

            if (userInput[2] < '0' || userInput[2] > '9'){

                incorrectInput = true;
            }
        }

        if (incorrectInput){

            cout<< " Incorrect Move!!! Please enter a correct move ---> ";
            getline(cin, userInput);
            incorrectInput = false;
        }
        else{

            incorrectInput = true;
        }
    }

    rowMove = toLower(userInput[0]);
    userMoves[0] = rowMove - 'a';
    if (userInput.length() == 2){

        userMoves[1] = (userInput[1] - '1');
    }
    else{

        userMoves[1] = ((userInput[1] - '0') * 10) + (userInput[2]-'1');
    }

    return userMoves;
}

/*////////////////////////////////////////////////////////////////

    Get the player, the Board and the move
    - check if the position is occupied
    - check if it a right column move
    Return an array which contains the {row position, column position}

//////////////////////////////////////////////////////////////////*/

int* checkUserPosition(int* playerMove, Board& playingBoard, Player currentPlayer){
    string userMove;
    char** gameBoard = playingBoard.getBoard();
    int row = playerMove[0];
    int column = playerMove[1];

    while(column >= playingBoard.getColumn() || gameBoard[row][column] != ' '){

        cout<< " Incorrect Move!!! Please enter a correct move ---> ";
        getline(cin, userMove);
        playerMove = checkUserMoves(userMove, playingBoard);
        row = playerMove[0];
        column = playerMove[1];

    }
    return playerMove;
}

/*////////////////////////////////////////////////////////////////

    Get the number of players from the user
    - verify the input is correct and it is between MIN and MAX
        values given
    Return the number of players

//////////////////////////////////////////////////////////////////*/

int getNumberOfPlayer(){

    string numberOfPlayers;
    int numberOfPlayers_int;
    cout<<" Please enter the number of players. choose from 2 to 5 players ---> ";
    getline(cin, numberOfPlayers);

    numberOfPlayers_int = numberOfPlayers[0] - '0';
    while (numberOfPlayers.length()!= 1 ||
            numberOfPlayers_int < MIN_NUMBER_PLAYERS ||
            numberOfPlayers_int > MAX_NUMBER_PLAYERS)
        {

            cout<<" Incorrect input! Please enter the number of players ---> ";
            getline(cin, numberOfPlayers);
            numberOfPlayers_int = numberOfPlayers[0] - '0';

        }
    numberOfPlayers_int = numberOfPlayers[0] - '0';
    return numberOfPlayers_int;

}

/*////////////////////////////////////////////////////////////////

    Get the number of players
    - Create an array of players by using the number of players
    - Initialize the the player piece and stat
    Return the number of players

//////////////////////////////////////////////////////////////////*/

Player* create_Players(int numberOfPlayers){

    Player* gamePlayers = nullptr;
    gamePlayers = new Player[numberOfPlayers];

    for (int i = 0; i < numberOfPlayers; i++){

        gamePlayers[i].piece = 'a' + i;
        gamePlayers[i].gamesWon = 0;
        gamePlayers[i].gamesLoss = 0;
        gamePlayers[i].gamesDrawn = 0;

    }

    return gamePlayers;
}
/*////////////////////////////////////////////////////////////////

    Get the number of players
    - Ask the user for their name
    - check for if there is any mistake or error
    - capitalize the first letter of the every part of the name
    Return the final full name

//////////////////////////////////////////////////////////////////*/

string getName(int player_number){

    string user_Name;

    cout<< endl<<" Please Enter Name for Player "<< player_number + 1 << " ---> ";
    getline(cin, user_Name);

    user_Name = remove_spaces(user_Name);
    user_Name = toLowerCaseString(user_Name);

    while(check_Characters(user_Name) || !checkNoLastName(user_Name)){
        cout<< " Incorrect Input!!! Please Enter correct name for Player"<< player_number +1 << " ---> ";
        getline(cin, user_Name);
        user_Name = remove_spaces(user_Name);
        user_Name = toLowerCaseString(user_Name);
    }


    user_Name = changeToCapital(user_Name);

    return user_Name;
}
/*////////////////////////////////////////////////////////////////

    Get the user name
    - verify if the input has only characters

    Return a boolean after checking

//////////////////////////////////////////////////////////////////*/

bool check_Characters(string user_Name){
    bool isNotCharacter;
    int numOfSpace = 0;

    isNotCharacter = false;

    for (int i = 0; i < user_Name.length(); i++){

        if ((user_Name[i] < 'a' || user_Name[i] >'z') && user_Name[i] != ' '){

            isNotCharacter = true;
        }

        if (user_Name[i] == ' '){

            numOfSpace++;
        }
    }

    if (user_Name.length() < 1){
string* multiplyNumbers(string number1, string number2);
        isNotCharacter = true;
    }
    if (numOfSpace == 0){

        isNotCharacter = true;
    }

    return isNotCharacter;
}

/*////////////////////////////////////////////////////////////////

    Get the user name
    - verify if the input has a last name
    Return a boolean after checking

//////////////////////////////////////////////////////////////////*/
bool checkNoLastName(string userName){

    bool hasLastName = false;
    int indexOfString = 0;
    userName = toLowerCaseString(userName);

    while ((indexOfString < userName.length()) && !hasLastName){

        if (userName[indexOfString] == ' '){

            if (userName[indexOfString + 1] >= 'a' && userName[indexOfString + 1] <= 'z'){

                hasLastName = true;

            }
        }


        indexOfString++;
    }

    return hasLastName;
}

/*////////////////////////////////////////////////////////////////

    Get the user name
    - change every letter to small letter
    Return a boolean after checking

//////////////////////////////////////////////////////////////////*/

string toLowerCaseString(string user_Name){
    string lowerCase;

    for (int i = 0; i <  user_Name.length(); i++){

        lowerCase += toLower(user_Name[i]);
    }
    return lowerCase;
}

/*////////////////////////////////////////////////////////////////

    Get the user name
    - remove any extra spaces in the name
    Return the name

//////////////////////////////////////////////////////////////////*/

string remove_spaces(string Player_name){

    string full_Name="";
    bool is_Firstletter = false;
    int Space_count = 0;

    for (int i = 0; i < Player_name.length(); i++){

        if (Player_name[i] != ' ' || is_Firstletter){

            full_Name += Player_name[i];
            is_Firstletter = true;
        }
    }

    Player_name = full_Name;
    full_Name = "";

    for (int i = 0; i < Player_name.length(); i++){

        if (Player_name[i] == ' ' && Space_count == 0){

            full_Name += " ";
            Space_count++;
        }

        if (Player_name[i] != ' '){

            full_Name += Player_name[i];
            Space_count=0;
        }

    }

    return full_Name;

}

/*////////////////////////////////////////////////////////////////

    Get the user name
    - capitalize the first letter
    Return final letter

//////////////////////////////////////////////////////////////////*/

string changeToCapital(string userName){

    string name;
    name += toUpper(userName[0]);
    for (int i = 1; i < userName.length(); i++){

        if (userName[i-1] == ' '){

            name += toUpper(userName[i]);
        }
        else{

            name += toLower(userName[i]);

        }

    }
    return name;
}

/*////////////////////////////////////////////////////////////////

    Get the user name
    - get the first name from the name
        - move over the string until you get a space

    Return the final string as the first name

//////////////////////////////////////////////////////////////////*/

string getFirstName(string userName){

    string firstName;
    int indexofString;

    indexofString = 0;
    while (userName[indexofString] != ' '){

        firstName += userName[indexofString];
        if(indexofString == userName.length()){
            break;
        }
        indexofString++;

    }

    return firstName;
}

/*////////////////////////////////////////////////////////////////

    Get the Max size, trigger if it is row or column
    - get the row or column size
    - verify if the input is correct
    Return the final size

//////////////////////////////////////////////////////////////////*/

int getSize(const int MAX_SIZE, char rowOrCol){

    int final_size;
    string userSizeInput;

    if(rowOrCol == 'r'){
        cout << " Enter the number of rows    ->  ";
    }
    else{
        cout << " Enter the number of columns ->  ";
    }
    getline(cin, userSizeInput);

    if (userSizeInput.length() == 1){

        final_size = userSizeInput[0] - '0';
    }
    if (userSizeInput.length() == 2){

        final_size = (userSizeInput[0] - '0') * 10 + (userSizeInput[1] - '0');
    }


    while (final_size < MIN_ROW_SIZE || final_size > MAX_SIZE ||
            userSizeInput.length() < 1 || userSizeInput.length() > 2){

        cout<< " Incorrect Input!!! Please enter the correct size ---> ";
        getline(cin, userSizeInput);

        if (userSizeInput.length() == 1){

            final_size = userSizeInput[0] - '0';
        }

        if (userSizeInput.length() == 2){

            final_size = (userSizeInput[0] - '0') * 10 + (userSizeInput[1] - '0');
        }
    }

    return final_size;

}

/*////////////////////////////////////////////////////////////////

    Gets the players who won and number of players
    - updates each player's draw if it is a draw
    - updates win and losses if there is a win

//////////////////////////////////////////////////////////////////*/

void update_Status(Player* gamePlayers, int turn, int numberOfPlayers){

    for (int i = 0; i < numberOfPlayers; i++){

        if (turn == numberOfPlayers){

            gamePlayers[i].gamesDrawn++;
        }
        if (i == turn){
            gamePlayers[i].gamesWon++;
        }
        if ((turn != numberOfPlayers) && (i != turn)){
            gamePlayers[i].gamesLoss++;
        }
    }
}

/*////////////////////////////////////////////////////////////////

    Gets the game players and number of players
    Displays final stat

//////////////////////////////////////////////////////////////////*/

void printStat(Player* gamePlayers, int numberOfPlayers){

    string longest_name = "";

    for (int i = 0 ; i < numberOfPlayers; i++){

        if( (gamePlayers[i].fullName).length() > longest_name.length()){
        longest_name = gamePlayers[i].fullName;
        }
    }
    cout<<" "<< setw(longest_name.length() + 1)<< "  " << " ------ ------ ------"<< endl;
    cout<<" "<< setw(longest_name.length() + 1)<< "  " << "|  WIN | Loss | Draw |"<< endl;
    cout<<" "<< setw(longest_name.length() + 1)<< "  " << " ------ ------ ------"<< endl;

    for (int i = 0; i < numberOfPlayers; i++){

        cout<<" "<< setw(longest_name.length())<< gamePlayers[i].fullName<< " | ";
        cout<<setw(4) << gamePlayers[i].gamesWon<< " | "<< setw(4) << gamePlayers[i].gamesLoss;
        cout<< " | "<< setw(4) << gamePlayers[i].gamesDrawn <<" | "<< endl;
        cout<< " "<<setw(longest_name.length())<< " " << "  ------ ------ ------"<< endl;
    }
}

/*////////////////////////////////////////////////////////////////

    Prints the Opening guide

//////////////////////////////////////////////////////////////////*/

void openningStatement(){

    cout<< endl;
    cout<<" Welcome Players to Tic Tac Toe!!!"<< endl;
    cout<<" Here you can play with 2 to 5 people in this game."<< endl;
    cout<<" The size of the board can be between 3 x 3 to 11 x 14. " << endl;
    cout<< endl<<" You can enter players names before the game however the names " << endl;
    cout<<" has to be in characters (NO NUMBERS OR SYMBOLS!!!) and must have ";
    cout<<"first and last name." << endl;
    cout<<endl<<" To make a move enter the row letter then the column number Example: A10"<< endl;
    cout<<" You can play this game Multiple times with changing the board size "<< endl;
    cout<<" after every game. Know that you cannot increase or decrease the number";
    cout<<" every game."<< endl;


    cout<<endl<< endl<<" Enjoy the game!!!" << endl;
}
