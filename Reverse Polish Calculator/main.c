#include <stdio.h>
#include <stdlib.h>
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
      if (a == -1) { // Check for pop error
        return -1; // Indicate error
      }
      b = pop(ps);
      if (b == -1) { // Check for pop error
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
    return -1; // Indicate error
  }

  return pop(ps);
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
