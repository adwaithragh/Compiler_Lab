%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);

int isValid = 1;
%}

%token IDENTIFIER

%%

input:
      /* empty */
    | input line
    ;

line:
      IDENTIFIER '\n' {
                        if (isValid)
                            printf("Valid identifier\n");
                        else
                            printf("Invalid identifier\n");
                        isValid = 1;
                      }
    | '\n' {
              printf("Empty line\n");
              isValid = 1;
           }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
int main(void) {
    printf("Enter an identifier:\n");
    return yyparse();
}

