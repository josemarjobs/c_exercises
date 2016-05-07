/*********************************************************************
************************* Prologue ***********************************
* University of California Extension, Santa Cruz
* Advanced C Programming
* Instructor: Rajainder A. Yeldandi
* Author: Josemar da Costa Magalhaes
* Assignment Number: 7
* Topic: Backtrackings
* Filename: queens.c
* Date: 05/06/2016
* Objective: Place 8 Queens in a chessboard without atacking one another
*********************************************************************/


/*********************************************************************
* PROGRAM ELEMENTS
* preprocessor directives
*********************************************************************/
#include<stdio.h>
#define BOARDSIZE 8
#define DIAGONAL (2 * BOARDSIZE - 1)
#define DOWNOFFSET 7
#define FALSE 0
#define TRUE 1

/*********************************************************************
* Function prototypes
*********************************************************************/
void writeBoard (void);
void clearBoard (void);
void addQueen (void);

/*********************************************************************
* Global Variables
*********************************************************************/
FILE *output;
int queencol [BOARDSIZE]; /* queen column */
int colfree [BOARDSIZE]; // is column free
int upfree [DIAGONAL]; // up diagonal free
int downfree [DIAGONAL]; //down diagonal free
int queencount = -1; // row queen is placed
int numsol = 0; // number of solutions found

int main (void) {
  char op, keystroke;
  int i, colNumber;
  output = fopen("output-queens.txt", "a");

  do {
    do {
      printf("Insert the column number to place the queen (From 0 to 7): ");
      scanf("%d", &colNumber);
      fprintf(output, "Insert the column number to place the queen (From 0 to 7): %d\n", colNumber);
    } while(colNumber < 0 || colNumber > 7);

    clearBoard();
    // Place the queen in the given position and mark it as not free
    queencol[++queencount] = colNumber;
    upfree[queencount + colNumber] = FALSE;
    downfree [queencount - colNumber + DOWNOFFSET] = FALSE;
    colfree[queencount + colNumber] = FALSE;
    addQueen();

    printf("Continue? (y/N): ");
    scanf("%c%c",&keystroke,&op);
    fprintf(output, "Continue? (y/N): %c\n", op);
  } while (op == 'y'); // Y continue, any other key Ends the program.

  fclose(output);

  return 0;
} /* end of main function */


/*********************************************************************
Function: addQueen()
input:   void
return: void

Desription: Add the remaining queens to the board, backtracking to
            avoid colisions
*********************************************************************/
void addQueen (void) {
  int col;
  queencount++;

  for(col = 0; col < BOARDSIZE; col++) {
    if (colfree[col] && upfree[queencount + col]
        && downfree[queencount-col+DOWNOFFSET]) {
      // put the queen in (queencount, col)
      queencol[queencount] = col;
      colfree[col] = FALSE;
      upfree[queencount + col] = FALSE;
      downfree[queencount - col + DOWNOFFSET] =  FALSE;

      if (queencount == BOARDSIZE - 1) { // Done, print the configuration
        printf("\n %d Queen Solution: %d\n\n", 8, ++numsol);
        fprintf(output, "\n %d Queen Solution: %d\n\n", 8, numsol);
        writeBoard();
      } else {
        addQueen();
      }

      if (queencount - 1 < 0) {
        continue;
      }
      // remove the last queen and free up spaces
      colfree[col] = TRUE;
      upfree[queencount - 1 + col] = TRUE;
      downfree[queencount - 1 - col + DOWNOFFSET] =  TRUE;
      queencount--;
    }
  }
}

/*********************************************************************
Function: writeBoard()
input:   void
return: void

Desription: Write the board in a matrix way
*********************************************************************/
void writeBoard(void) {
  int col;
  static int qcount = 0;
  for(col=0; col<BOARDSIZE; col++) {
    if (qcount == 0 && queencol[qcount] == col) {
      printf("U    ");
      fprintf(output, "U    ");
    } else if (queencol[qcount] == col) {
      printf("Q    ");
      fprintf(output, "Q    ");
    } else {
      printf("*    ");
      fprintf(output, "*    ");
    }
  }
  printf("\n\n");
  fprintf(output, "\n\n");
  if (qcount++ < BOARDSIZE - 1) {
    writeBoard();
    qcount = 0;
  }
}

/*********************************************************************
Function: clearBoard()
input:   void
return: void

Desription: Free up the board's columns, rows and diagonals.
*********************************************************************/
void clearBoard(void) {
  for(int i = 0; i<BOARDSIZE; i++) {
    colfree[i] = TRUE;
    queencol[i] = -1;
  }
  for(int j = 0; j<DIAGONAL; j++) {
    upfree[j] = TRUE;
    downfree[j] = TRUE;
  }
  queencount = -1;
}
