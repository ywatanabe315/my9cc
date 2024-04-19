#include <stdlib.h>
#include <stdio.h>
#include "9cc.h"

void gen_lval(Node *node) {
  if (node->kind != ND_LVAR)
    error("左辺値が変数ではありません。");
  printf("  mov rax, rbp\n");
  printf("  sub rax, %d\n", node->offset);
  printf("  push rax\n");
}

void gen(Node *node) {
  switch (node->kind) {
    case ND_NUM:
      printf("  push %d\n", node->val);
		  return;
    case ND_LVAR:
      gen_lval(node);
      printf("  pop rax\n");
      printf("  mov rax, [rax]\n");
      printf("  push rax\n");
      return;
    case ND_ASSIGN:
      gen_lval(node->lhs);
      gen(node->rhs);

      printf("  pop rdi\n");
      printf("  pop rax\n");
      printf("  mov [rax], rdi\n");
      printf("  push rdi\n");
      return;
    case ND_RETURN:
      gen(node->lhs);
      printf("  pop rax\n");
      printf("  mov rsp, rbp\n");
      printf("  pop rbp\n");
      printf("  ret\n");
      return;
    case ND_IF:
      // 条件
      gen(node->lhs);
      printf("  pop rax\n");
      printf("  cmp rax, 0\n");
      if (node->rhs->kind == ND_ELSE) {
        printf("  je %s\n", ".Lelse1");
        //　ifブロック
        gen(node->rhs->lhs);
        printf("  jmp .Lend1\n");
        printf("%s\n", ".Lelse1:");
        // elseブロック
        gen(node->rhs->rhs);
      } else {
        printf("  je %s\n", ".Lend1");
        //　ifブロック
        gen(node->rhs);
      }

      printf("%s\n", ".Lend1:");
      return;
    case ND_WHILE:
      printf(".Lbegin1:\n");
      gen(node->lhs);
      printf("  pop rax\n");
      printf("  cmp rax, 0\n");
      printf("  je %s\n", ".Lend1");
      gen(node->rhs);
      printf("  jmp %s\n", ".Lbegin1");
      printf("%s\n", ".Lend1:");
      return;
  }

	gen(node->lhs);
	gen(node->rhs);

	printf("  pop rdi\n");
	printf("  pop rax\n");

	switch (node->kind) {
		case ND_ADD:
			printf("  add rax, rdi\n");
			break;
		case ND_SUB:
			printf("  sub rax, rdi\n");
			break;
		case ND_MUL:
			printf("  imul rax, rdi\n");
			break;
		case ND_DIV:
			printf("  cqo\n");
			printf("  idiv rdi\n");
			break;
		case ND_EQ:
			printf("  cmp rax, rdi\n");
			printf("  sete al\n");
			printf("  movzb rax, al\n");
			break;
		case ND_NE:
			printf("  cmp rax, rdi\n");
			printf("  setne al\n");
			printf("  movzb rax, al\n");
			break;
		case ND_LT:
			printf("  cmp rax, rdi\n");
			printf("  setl al\n");
			printf("  movzb rax, al\n");
			break;
		case ND_LE:
			printf("  cmp rax, rdi\n");
			printf("  setle al\n");
			printf("  movzb rax, al\n");
			break;
	}

	printf("  push rax\n");
}
