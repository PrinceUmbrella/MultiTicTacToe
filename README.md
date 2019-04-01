CSC310-01 Data Structures and Algorithm Analysis (Spring 2019) Assignment 2 Due Date: Friday, February 8, 2019 
 
Extend the 3 by 3 “Tic-Tac-Toe” program in assignment #1 to allow up to 5 players and any board size (m by n) including the following features: 
 
1. The program would allow 2 and up to 5 human players. 
2. The program will capture player’s full names. The players’ names are entered one player at a time per line.  
    A valid player’s name consists of only alphabet letters separated by space.  All players’ names should be in the format of starting with a capitalized letter and followed by lower case letters. 
3. Only the first names of players are to be used in subsequent prompt messages (#8 below). You can assume that the first word in player’s full name is the first name. You can accept the rest of the input as it is other part of player’s name. However, the full name will be used in displaying game statistics (#12 below)  
4. The first player’s piece is “a”, the second player’s piece is “b”, and so on. The seventh player’s piece is “e”.  The players keep their pieces throughout the game.
5. The players can specify the size of the board (up to 11 by 14) for each game.  The number of rows and columns are input on separate prompts. Each game might have a different board size.  The minimum size of the board is 3 by 3.
6. Player with “a” starts the first game.  The order of players will be in the round robin sequence “a”..”e” and then back to “a”. 
7. The initial game board (example: 4 X 6) should exactly like the one below: 
8. The move is specified as row character (A..K, or a..k), followed by column number (1..14) in a single entry, e.g. D5, J12, b4, d6, etc.   The row character can be upper case or lower case. 
9. The program would redraw the board after each move. 
10. A player wins the game if he has three of his pieces consecutively horizontally, vertically or diagonally anywhere in the board. 
11. If one player wins, at least one of the possible winning configurations will be displayed on the board in upper case of his/her piece. 
12. At the end of each game, the program would display the total number of games played and the number of games each player wins, loses and draws in a table form.  The full names of the players are used in the statistic display and are aligned right.  The number in the statistics also aligned right (assuming a maximum of 1000 games can be played any time. An example of such statistics is as below:  
13. If a game ends with someone winning, the next game starts with the player AFTER the winner of the previous game in the round robin sequence, i.e. the winner of the previous game will be the last one in the next game. 14. If a game ends in a draw, the next game starts with the players after the previous game starter in the round robin sequence. 15. The program would allow multiple games to be played until the players select to quit at the end of any game. 
 
 # MultiTicTacToe
