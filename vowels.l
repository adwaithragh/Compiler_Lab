%option noyywrap
%{
        int vowels = 0;
        int consonants = 0;
%}
%%
[aeiouAEIOU] {vowels++;}
[a-zA-Z] {consonants++;}
.
\n {return 0;}
%%
int main()
{
        yylex();
        printf("Number of vowels = %d\nNumber of consonants = %d\n", vowels,consonants);
        return 0;
}
