#include <stdio.h>
#include <ctype.h> // For isdigit()
#include <math.h>  // For pow()
#include <string.h> // For strlen()
#include<stdlib.h>

#define MAXSIZE 100

typedef struct stack {
  int stack[MAXSIZE];
  int Top;
} NODE;

void push(NODE *pu, int item) {
  if (pu->Top == MAXSIZE - 1) {
    printf("\nThe Stack Is Full");
  } else {
    pu->Top++;
    pu->stack[pu->Top] = item;
  }
}

int pop(NODE *po) {
  int item;
  if (po->Top == -1) {
    printf("\nThe Stack Is Empty. Invalid Postfix expression");
    return -1; // Indicate error (optional)
  } else {
    item = po->stack[po->Top--];
  }
  return item;
}

int Postfix_Eval(char postfix[]) {
  int a, b, temp, len;
  NODE *ps = (NODE *)malloc(sizeof(NODE)); // Allocate memory for the stack
  ps->Top = -1;

  len = strlen(postfix);
  for (int i = 0; i < len; i++) {
    if (isdigit(postfix[i])) {
      // Operand is pushed on the stack (convert ASCII to integer)
      push(ps, postfix[i] - 48);
    } else {
      // Pop the top two operands for operation
      a = pop(ps);
      if (a == -1) { // Check for pop error (optional)
        return -1; // Indicate error
      }
      b = pop(ps);
      if (b == -1) { // Check for pop error (optional)
        return -1; // Indicate error
      }
      switch (postfix[i]) {
        case '+':
          temp = b + a;
          break;
        case '-':
          temp = b - a;
          break;
        case '*':
          temp = b * a;
          break;
        case '/':
          if (a == 0) {
            printf("\nDivision by zero error\n");
            return -1; // Indicate error
          }
          temp = b / (a *1.0);
          break;
        case '%':
          if (a == 0) {
            printf("\nModulo by zero error\n");
            return -1; // Indicate error
          }
          temp = b % a;
          break;
        case '^':
          temp = pow(b, a);
          break;
        default:
          printf("\nInvalid operator in postfix expression\n");
          return -1; // Indicate error
      }
      push(ps, temp);
    }
  }

  if (ps->Top != 0) {
    printf("\nInvalid postfix expression (extra operands)\n");
    return -1; // Indicate error (optional)
  }

  return pop(ps);
}

int main() {
  char choice, postfix[MAXSIZE];
  NODE *ps; // Declare ps within main

  do {
    printf("\nEnter the Postfix expression = ");
    scanf("%s", postfix);

    int result = Postfix_Eval(postfix);
    if (result != -1) {
      printf("\nThe postfix evaluation is = %d\n", result);
    }

    printf("\nDo you want to continue (Y/y) = ");
    fflush(stdin);
    scanf(" %c", &choice); // Use space before %c to consume newline
  } while (choice == 'Y' || choice == 'y');

  free(ps); // Deallocate memory for the stack

  return 0;
}
