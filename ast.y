/* ast.y - build AST for arithmetic expressions */
%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex(void);
void yyerror(const char *s);
%}

/* semantic value types */
%union {
    ASTNode *node;
    int num;
}

/* tokens */
%token <num> NUM

/* nonterminals */
%type <node> expr

/* operator precedence */
%left '+' '-'
%left '*' '/'
%left UMINUS

%%
input:
      /* empty */
    | input line
    ;

line:
      '\n'
    | expr '\n'    { 
                      print_ast($1); 
                      printf("\n"); 
                      /* Note: memory freeing not shown here; add free_ast() if needed */ 
                    }
    ;

expr:
      NUM                         { $$ = make_leaf($1); }
    | expr '+' expr              { $$ = make_node('+', $1, $3); }
    | expr '-' expr              { $$ = make_node('-', $1, $3); }
    | expr '*' expr              { $$ = make_node('*', $1, $3); }
    | expr '/' expr              { $$ = make_node('/', $1, $3); }
    | '-' expr %prec UMINUS      { /* unary minus — represent with '~' (or choose another marker) */
                                    $$ = make_node('~', NULL, $2);
                                  }
    | '(' expr ')'               { $$ = $2; }
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

int main(void) {
    printf("Enter expressions (one per line). Ctrl+D to exit.\n");
    return yyparse();
}
