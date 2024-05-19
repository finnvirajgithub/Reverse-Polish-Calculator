#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");
    return 0;
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