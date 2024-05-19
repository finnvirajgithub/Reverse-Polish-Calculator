// Y.M.D.Bandara


#include <stdio.h>
#include <stdlib.h> // For malloc and free
#include <string.h>  // For strlen

#define MAXSIZE 100

typedef struct stack {
  char stack[MAXSIZE];
  int Top;
} NODE;

void push(NODE *pu, char item) {
  if (pu->Top == MAXSIZE - 1) {
    printf("\nThe Stack Is Full");
  } else {
    pu->Top++;
    pu->stack[pu->Top] = item;
  }
}//(2+4)*6/3+1^2/4    24+6*3/12^4/+

char pop(NODE *po) {
  char item = '#';
  if (po->Top == -1) {
    printf("\nThe Stack Is Empty. Invalid Infix expression");
  } else {
    item = po->stack[po->Top--];
  }
  return item;
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

int main() {
  char infix[MAXSIZE];

  printf("Enter infix expression: ");
  scanf("%s", infix);

  Infix_Postfix(infix);

  return 0;
}
