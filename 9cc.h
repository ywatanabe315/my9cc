typedef enum {
	TK_RESERVED,
  TK_IDENT,
	TK_NUM,
	TK_EOF,
  TK_RETURN,
  TK_IF,
  TK_ELSE,
} TokenKind;

typedef enum {
	ND_ADD,
	ND_SUB,
	ND_MUL,
	ND_DIV,
	ND_NUM,
	ND_EQ,
	ND_NE,
	ND_LT,
	ND_LE,
  ND_ASSIGN,
  ND_LVAR,
  ND_RETURN,
  ND_IF,
  ND_ELSE,
} NodeKind;

typedef struct Token Token;
struct Token {
	TokenKind kind;
	Token *next;
	int val;
	char *str;
	int len;
};

typedef struct Node Node;
struct Node {
	NodeKind kind;
	Node *lhs;
	Node *rhs;
	int val;
  int offset;
};

typedef struct LVar LVar;
struct LVar {
  LVar *next;
  char *name;
  int len;
  int offset;
};

Token *tokenize();
void program();
void gen(Node *node);
void error(char *fmt, ...);

extern char *user_input;
extern Token *token;
extern Node *code[];
extern LVar *locals;
