%{
#include <stdio.h>
#include "y.tab.h"
#define YYSTYPE char *
void debuglog(const char* x) {
}
%}

%% 
[0123456789]+ {yylval=yytext; debuglog("NUMBER\n");return NUMBER;}
[ \n\t\r]+    /**/
[\{] {yylval=yytext;  debuglog("LCBRACE\n");return LCBRACE; }
[\}] {yylval=yytext;  debuglog("RCBRACE\n");return RCBRACE; }
[A-Za-z_][A-Za-z0-9_]* {yylval=yytext;debuglog("WORD\n");return WORD;}
["] {yylval=yytext;  debuglog("QUOTE\n");return QUOTE; }
\[ {yylval=yytext;  debuglog("LSBRACE\n");return LSBRACE; }
= {yylval=yytext;  debuglog("EQUALS\n");return EQUALS; }
\] {yylval=yytext;  debuglog("RSBRACE\n");return RSBRACE; }
\[[01234567890]+\] {yylval=yytext;  debuglog("TAG\n");return TAG; }
%%
