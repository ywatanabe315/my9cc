#include <stdio.h>
#include "9cc.h"

char *user_input;
Token *token;

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "argument number invalid\n");
    return 1;
  }

	user_input = argv[1];
	token = tokenize();
	Node *node = expr();

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

	gen(node);

	printf("	pop rax\n");
  printf("  ret\n");
  return 0;
}
