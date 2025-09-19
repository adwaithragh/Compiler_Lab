#include <stdio.h>
#include <stdlib.h>

typedef struct ASTNode {
	char op;
	struct ASTNode *left;
	struct ASTNode *right;
	int value;
} ASTNode;
ASTNode* make_node(char op, ASTNode* left, ASTNode* right);
ASTNode* make_leaf(int value);
void print_ast(ASTNode* node);
