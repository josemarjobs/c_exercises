/*********************************************************************
************************* Prologue ***********************************
* University of California Extension, Santa Cruz
* Advanced C Programming
* Instructor: Rajainder A. Yeldandi
* Author: Josemar da Costa Magalhaes
* Assignment Number: 6
* Topic: GAME TIC TAC TOE
* Filename: tictactoe.c
* Date: 04/19/2016
* Objective: Create a game TIC TAC TOE
*********************************************************************/


/*********************************************************************
* PROGRAM ELEMENTS
* preprocessor directives
*********************************************************************/
#include<stdio.h>
#include<string.h>
#define SIZE 4

/*********************************************************************
* GLOBAL VARIABLES
*********************************************************************/

// game board 4x4
char *board[SIZE][SIZE] = {
  {" 1"," 2"," 3"," 4"},
  {" 5"," 6"," 7"," 8"},
  {" 9","10","11","12"},
  {"13","14","15","16"}
};
// output file
FILE *file;

/*********************************************************************
Function: displayBoard
input:   nome
return: void

Desription: Displays the game board in an organized and matrix way.
*********************************************************************/
void displayBoard() {
  printf("+----+----+----+----+\n");
  fprintf(file, "+----+----+----+----+\n");
  for(int i = 0; i<SIZE; i++){
    for(int j = 0; j<SIZE; j++){
      printf("| %s ", board[i][j]);
      fprintf(file, "| %s ", board[i][j]);
    }
    printf("|\n");
    fprintf(file, "|\n");
    printf("+----+----+----+----+\n");
    fprintf(file, "+----+----+----+----+\n");
  }
}
/*********************************************************************
Function: isPositionOcupied()
input:
row, col - an int, the row and col to be checked
return: 0 for false, 1 for true

Desription: Check whether a given position is ocupied by X or O
********************************************************************/
int isPositionOcupied(int row, int col) {
  if (strcmp(board[row][col], " X") == 0 || strcmp(board[row][col], " O") == 0) {
    return 1;
  }
  return 0;
}

/*********************************************************************
Function: placePlayer()
input:
pos - an int, the position to be checked
player - the string representing the player
return: 0 when could not place the placer, 1 when it did place the placer

Desription: Check whether a given position is ocupied by X or O
********************************************************************/
int placePlayer(int pos, char *player) {
  // since the position is given by a single number between 1-16
  // it needs to be converted in a row and col
  int row = --pos/SIZE;
  int col = pos%SIZE;
  if (isPositionOcupied(row, col)) {
    return 0;
  }
  board[row][col] = player;
  return 1;
}

/*********************************************************************
Function: isPlayerInPos()
input:
row, col - ints, the row and col to be checked
player - the string representing the player
return: 0 when the player is not in that position, 1 for true

Desription: Check whether a given position is ocupied by a given player
********************************************************************/
int isPlayerInPos(int row, int col, char *player) {
  if(!strcmp(board[row][col], player)){
    return 1;
  }
  return 0;
}

/*********************************************************************
Function: checkRow()
input:
row - an int, the row to be checked
player - the string representing the player
return: 0 when there is something in the row other than that player, 1 otherwise

Desription: Check if a player was won in a given row
********************************************************************/
int checkRow(int row, char *player) {
  for(int col = 0; col<SIZE; col++) {
    if(!isPlayerInPos(row, col, player)){
      return 0;
    }
  }
  return 1;
}
/*********************************************************************
Function: checkCol()
input:
col - an int, the col to be checked
player - the string representing the player
return: 0 when there is something in the col other than that player, 1 otherwise

Desription: Check if a player was won in a given col
********************************************************************/
int checkCol(int col, char *player) {
  for(int row = 0; row<SIZE; row++) {
    if(!isPlayerInPos(row, col, player)){
      return 0;
    }
  }
  return 1;
}

/*********************************************************************
Function: checkMainDiag()
input:
player - the string representing the player
return: 0 when there is something in the diagonal other than that player, 1 otherwise

Desription: Check if a player was won in the main diagonal
********************************************************************/
int checkMainDiag(char *player) {
  for(int i = 0; i<SIZE; i++) {
    if(!isPlayerInPos(i, i, player)){
      return 0;
    }
  }
  return 1;
}

/*********************************************************************
Function: checkSecDiag()
input:
player - the string representing the player
return: 0 when there is something in the sec diagonal other than that player, 1 otherwise

Desription: Check if a player was won in the secondary diagonal
********************************************************************/
int checkSecDiag(char *player) {
  for(int i = 0, j = SIZE-1; i<SIZE; i++, j--) {
    if(!isPlayerInPos(i, j, player)){
      return 0;
    }
  }
  return 1;
}


/*********************************************************************
Function: hasPlayerWon()
input:
player - the string representing the player
return: 0 for false, 1 for true

Desription: Check if a player was won the game
********************************************************************/
int hasPlayerWon(char *player) {
  for(int i = 0; i<SIZE; i++) {
    if (checkRow(i, player) || checkCol(i, player)) {
      return 1;
    }
  }
  if (checkMainDiag(player) || checkSecDiag(player)){
    return 1;
  }
  return 0;
}

int main() {
  file  = fopen("file2.txt", "w");
  int pos, winner = 0;

  displayBoard();
  for(int i = 0; i<(SIZE*SIZE);) {
    PLAYER1:
    printf("Player 1 input the square number to place your X: ");
    scanf("%d",&pos);
    fprintf(file, "Player 1 input the square number to place your X: %d\n", pos);

    // Positions above 16 are invalid
    if(pos > 16){
      printf("Position %d is invalid. Selec a new Position\n", pos);
      fprintf(file, "Position %d is invalid. Selec a new Position\n", pos);
      goto PLAYER1;
    }
    if(!placePlayer(pos, " X")){
      printf("Position %d already in use. Select a new position\n", pos);
      fprintf(file, "Position %d already in use. Select a new position\n", pos);
      goto PLAYER1;
    }
    if(hasPlayerWon(" X")){
      winner = 1;
      break;
    }
    displayBoard();
    i++;

    PLAYER2:
    printf("Player 2 input the square number to place your O: ");
    scanf("%d",&pos);
    fprintf(file, "Player 2 input the square number to place your O: %d\n", pos);

    // Positions above 16 are invalid
    if(pos > 16){
      printf("Position %d is invalid. Selec a new Position\n", pos);
      fprintf(file, "Position %d is invalid. Selec a new Position\n", pos);
      goto PLAYER1;
    }
    if(!placePlayer(pos, " O")){
      printf("Position %d already in use. Select a new position\n", pos);
      fprintf(file, "Position %d already in use. Select a new position\n", pos);
      goto PLAYER2;
    }
    if(hasPlayerWon(" O")){
      winner = 2;
      break;
    }
    displayBoard();
    i++;
  }

  printf("\n\nGAME OVER\n");
  fprintf(file, "\n\nGAME OVER\n");
  if (winner) {
    printf("Player %d has won\n\n", winner);
    fprintf(file, "Player %d has won\n\n", winner);
  } else {
    printf("It's a draw.\n\n");
    fprintf(file, "It's a draw.\n\n");
  }
  displayBoard();

  fclose(file);
  return 0;
}
