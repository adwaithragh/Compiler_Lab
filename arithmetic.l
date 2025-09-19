%{
#include "y.tab.h"
%}

%%
[a-zA-Z]+       { return ALPHA;}
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[ \t]           ;
\n              { return '\n'; }
[-+*/()]{1}     { return yytext[0]; }

.               { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
