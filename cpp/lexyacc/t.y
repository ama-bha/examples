%{
#include<stdio.h>
#define YYSTYPE char *
%}

%start expr
%token NUMBER TAG DOUBLE WS QUOTE LCBRACE LSBRACE RCBRACE RSBRACE WORD EQUALS
%%

expr        :WORD LCBRACE assnlist RCBRACE
            {
              printf("%s,%s,%s,%s\n",$1,$2,$3,$4);
            }
            ;
assnlist    : 
            | assn assnlist
            ;
assn        : WORD EQUALS NUMBER
            {
              printf("%s\n",$3);
            }
word        : WORD
            {

            }


%%

int main(void)
{
    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "*%s*\n", s);
    return 0;
}

