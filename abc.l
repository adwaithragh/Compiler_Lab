%option noyywrap
%{
        #include <stdio.h>
%}
%%
abc {printf("ABC");}
.|\n {printf("%s", yytext);}
%%
int main()
{
        printf("Enter a string: ");
        yylex();
        return 0;
}

