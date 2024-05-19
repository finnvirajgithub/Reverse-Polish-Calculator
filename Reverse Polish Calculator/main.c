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
int prec(char symbol) {
  switch (symbol) {
    case '(':
      return 1;
    case ')':
      return 2;
    case '+':
    case '-':
      return 3;
    case '*':
    case '/':
    case '%':
      return 4;
    case '^':
      return 5;
    default:
      return 0;
  }
}
void Infix_Postfix(char infix[]) {
  int len = strlen(infix);
  char postfix[MAXSIZE], ch;

  // Allocate memory for the stack
  NODE *ps = (NODE *)malloc(sizeof(NODE));
  ps->Top = -1;

  // Add ending parenthesis
  infix[len++] = ')';
  push(ps, '(');

  for (int i = 0, j = 0; i < len; i++) {
    switch (prec(infix[i])) {
      case 1:
        push(ps, infix[i]);
        break;
      case 2:
        ch = pop(ps);
        while (ch != '(') {
          postfix[j++] = ch;
          ch = pop(ps);
        }
        break;
      case 3:
      case 4:
      case 5:
        ch = pop(ps);
        while (prec(ch) >= prec(infix[i])) {
          postfix[j++] = ch;
          ch = pop(ps);
        }
        push(ps, ch);
        push(ps, infix[i]);
        break;
      default:
        postfix[j++] = infix[i];
        break;
    }
  }

  // Free allocated memory for the stack
  free(ps);

  printf("\nThe Postfix expression is = ");
  printf("%s\n", postfix); // Use strlen(postfix) for safety
}