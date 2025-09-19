%{
#include "y.tab.h"
extern int isValid;
%}

%%

[a-zA-Z][a-zA-Z0-9]*    { return IDENTIFIER; }
[ \t]                  ;
\n                     { return '\n'; }

.                      {
                        printf("Invalid character: %s\n", yytext);
                        isValid = 0;
                       }

%%

int yywrap() {
    return 1;
}

