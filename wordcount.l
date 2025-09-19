%option noyywrap
%{
        #include <stdio.h>
        int lines=0,words=0,chars=0;
%}
%%
\n {lines++;chars++;}
[a-zA-Z0-9]+ {words++;chars+=yyleng;}
. {chars++;}
%%
int main(int argc, char *argv[])
{
        yyin = fopen(argv[1],"r");
        yylex();
        printf("\nTotal lines = %d\n",lines);
        printf("\nTotal words = %d\n",words);
        printf("\nTotal characters = %d\n",chars);
        fclose(yyin);
}
