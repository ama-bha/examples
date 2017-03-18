%{
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define YYSTYPE char *
char* strcat2(const char* a,const char* b) {
    char* ans = (char*)(malloc((strlen(a)+strlen(b)+1)*sizeof(char)));
    strcpy(ans,a);
    strcpy(ans+strlen(a),b);
    return ans;
}

char* strcat3(const char* a,const char* b,char* c) {
    char* ans = (char*)(malloc((strlen(a)+strlen(b)+strlen(c)+1)*sizeof(char)));
    strcpy(ans,a);
    strcpy(ans+strlen(a),b);
    strcpy(ans+strlen(a)+strlen(b),c);
    return ans;
}

%}

%union {

}

%start expr
%token NUMBER TAG DOUBLE WS QUOTE LCBRACE LSBRACE RCBRACE RSBRACE WORD EQUALS
%%

expr        :WORD LCBRACE assnlist RCBRACE
            {
              printf("%s%s%s%s\n",$1,"{",$3,"}");
            }
            ;
assnlist    : 
            | assn assnlist
            ;
assn        : WORD EQUALS NUMBER
            {
                $$ = strcat3($1,"=",$3);
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

