#include "ast.h"

ASTNode* make_node(char op, ASTNode* left, ASTNode* right) {
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->op = op;
        node->left = left;
        node->right = right;
        node->value = 0;
        return node; 
}

ASTNode* make_leaf(int value) {
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->op = 0;
        node->left = NULL;
        node->right = NULL;
        node->value = value;
        return node;
}

void print_ast(ASTNode* node) {
        if(node->left) print_ast(node->left);
        if(node->right) print_ast(node->right);
        if(node->op)
                printf("%c", node->op);
        else
                printf("%d", node->value);
}
