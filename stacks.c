/*********************************************************************
************************* Prologue ***********************************
* University of California Extension, Santa Cruz
* Advanced C Programming
* Instructor: Rajainder A. Yeldandi
* Author: Josemar da Costa Magalhaes
* Assignment Number: 8
* Topic: Temperature Conversion
* Filename: stacks.c
* Date: 05/06/2016
* Objective: Read and evaluate a sequence of symbols
*********************************************************************/


/*********************************************************************
* PROGRAM ELEMENTS
* preprocessor directives
*********************************************************************/
#include<stdio.h>
#include<stdlib.h>

#define MAXSTACK  50
#define EMPTYSTACK -1

/*********************************************************************
* Global Variables
*********************************************************************/
FILE *inputFile, *outputFile;

typedef struct {
  int top;
  char elements[MAXSTACK];
} STACK;

/*********************************************************************
Function: full()
input:   STACK
s - the stack to be checked
return: true or false

Desription: Checks to see if a given stack is full
*********************************************************************/
int full(STACK *s) {
  return s->top == (MAXSTACK - 1);
}

/*********************************************************************
Function: empty()
input:   STACK
s - the stack to be checked
return: true or false

Desription: Checks to see if a given stack is empty
*********************************************************************/
int empty(STACK *s) {
  return s->top == EMPTYSTACK;
}

/*********************************************************************
Function: pop()
input:   STACK
s - the stack to be altered
return: char - the last element removed from the stack

Desription: Remove the top element of the stack
*********************************************************************/
char pop(STACK *s) {
  if (empty(s)) {
    printf("Stack underflow\n");
    fprintf(outputFile, "Stack underflow\n");
    exit(1);
  }
  return s->elements[s->top--];
}

/*********************************************************************
Function: push()
input:   STACK, char
s - the stack to be altered
c - the element to be added to the stack
return: void

Desription: Add an element onto the stack
*********************************************************************/
void push(STACK *s, char c) {
  if (full(s)) {
    printf("Stack overflow\n");
    fprintf(outputFile, "Stack overflow\n");
    exit(1);
  } else {
    s->elements[++(s->top)] = c;
  }
}


int main() {
  STACK *stack;
  stack->top = EMPTYSTACK;
  inputFile = fopen("input.txt", "r");
  outputFile = fopen("output.txt", "w");

  char c;
  while((c = getc(inputFile)) != EOF) {
    if(c == '{' || c == '(' || c == '[') {
      printf("Pushed %c onto the stack\n", c);
      fprintf(outputFile, "Pushed %c onto the stack\n", c);
      push(stack, c);
    } else if (c == '}'){
      char last = pop(stack);
      printf("Found %c - ", c);
      fprintf(outputFile, "Found %c - ", c);
      if (last == '{') {
        printf("Matched %c last item popped out of the stack\n", last);
        fprintf(outputFile, "Matched %c last item popped out of the stack\n", last);
      } else {
        printf("Did not Match %c last item popped out of the stack\n", last);
        fprintf(outputFile, "Did not Match %c last item popped out of the stack\n", last);
        printf("\n\nInvalid sequence\n");
        fprintf(outputFile, "\n\nInvalid sequence\n");
        exit(1);
      }
    } else if (c == ')'){
      char last = pop(stack);
      printf("Found %c - ", c);
      fprintf(outputFile, "Found %c - ", c);
      if (last == '(') {
        printf("Matched %c last item popped out of the stack\n", last);
        fprintf(outputFile, "Matched %c last item popped out of the stack\n", last);
      } else {
        printf("Did not Match %c last item popped out of the stack\n", last);
        fprintf(outputFile, "Did not Match %c last item popped out of the stack\n", last);
        printf("\n\nInvalid sequence\n");
        fprintf(outputFile, "\n\nInvalid sequence\n");
        exit(1);
      }
    } else if (c == ']'){
      char last = pop(stack);
      printf("Found %c - ", c);
      fprintf(outputFile, "Found %c - ", c);
      if (last == '[') {
        printf("Matched %c last item popped out of the stack\n", last);
        fprintf(outputFile, "Matched %c last item popped out of the stack\n", last);
      } else {
        printf("Did not Match %c last item popped out of the stack\n", last);
        fprintf(outputFile, "Did not Match %c last item popped out of the stack\n", last);
        printf("\n\nInvalid sequence\n");
        fprintf(outputFile, "\n\nInvalid sequence\n");
        exit(1);
      }
    } else {
      printf("Ignored character\n");
      fprintf(outputFile, "Ignored character\n");
    }
  }

  printf("\n\nThe sequence was valid\n");
  fprintf(outputFile, "\n\nThe sequence was valid\n");

  fclose(outputFile);
  fclose(inputFile);
  return 0;
}
