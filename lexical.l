%option noyywrap

Prep     #.*
WhiteSp  ([ \n\t]+)
Punct    [,;\[\]\{\}]
String   \".*\"
Keyword  int|char|void|float|return|if|else|for|while|break|continue
Identifier [a-zA-Z_][0-9a-zA-Z_]*
Comment  "/*"([^*]|\*+[^*/])*\*+"/"
AssignOp "="|"+="|"-="|"*="|"/="
ArithOp  "+"|"-"|"*"|"/"|"%"
RelOp    "=="|"!="|"<="|">="|"<"|">"
LogiOp   "&&"|"||"|"!"
Integer  [0-9]+

%%

{WhiteSp}  {printf("\nWhite space detected.");}
{Prep}     {printf("\nPreprocessor :\t%s", yytext);}
{Punct}    {printf("\nPunctuation :\t%s", yytext);}
{Keyword}  {printf("\nKeyword :\t%s", yytext);}
{Identifier}: {printf("\nLabel :\t%s", yytext);}
{Identifier}  {printf("\nIdentifier :\t%s", yytext);}
{Comment}  {printf("\nComment :\t%s", yytext);}
{AssignOp} {printf("\nAssignOp :\t%s", yytext);}
{ArithOp}  {printf("\nArithOp :\t%s", yytext);}
{RelOp}    {printf("\nRelOp :\t%s", yytext);}
{LogiOp}   {printf("\nLogiOp :\t%s", yytext);}
{Integer}  {printf("\nInteger :\t%s", yytext);}
{String}   {printf("\nString :\t%s", yytext);}
%%

int main(int argc,char** argv){
    yyin = fopen(argv[1],"r");
    yylex();
    printf("\n");
    fclose(yyin);
}

