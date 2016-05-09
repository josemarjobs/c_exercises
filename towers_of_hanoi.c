/*********************************************************************
************************* Prologue ***********************************
* University of California Extension, Santa Cruz
* Advanced C Programming
* Instructor: Rajainder A. Yeldandi
* Author: Josemar da Costa Magalhaes
* Assignment Number: 10
* Topic: Stacks
* Filename: towers_of_hanoi.c
* Date: 05/08/2016
* Objective: Simulate the Towers of Hanoi
*********************************************************************/


/*********************************************************************
* PROGRAM ELEMENTS
* preprocessor directives
*********************************************************************/
#include<stdio.h>
/*********************************************************************
Function: move()
input:
char from - the PEG to move the DISK from
char to - the PEG to move the DISK to
char aux - the auxiliary peg to move the disks
int n - the number of disks
FILE file - the output file

Desription: Move n disks from the FROM PEG to the TO PEG.
*********************************************************************/

void move(char from, char to, char aux, int n, FILE *file) {
  if (n == 1) {
    printf("Moved disk %d from %c to %c\n", n, from, to);
    fprintf(file, "Moved disk %d from %c to %c\n", n, from, to);
    return;
  }
  move(from, aux, to, n-1, file);
  printf("Moved disk %d from %c to %c\n", n, from, to);
  fprintf(file, "Moved disk %d from %c to %c\n", n, from, to);
  move(aux, to, from, n-1, file);
}
/*********************************************************************
Function: main()
return: an integer.  0 if successful
Desription: Run the whole program
*********************************************************************/

int main() {
  FILE *file = fopen("output4disks.txt", "w");

  int n;
  printf("Enter the number of disks: ");
  scanf("%d", &n);
  fprintf(file, "Enter the number of disks: %d\n", n);

  move('A', 'C', 'B', n, file);

  fclose(file);
  return 0;
}
