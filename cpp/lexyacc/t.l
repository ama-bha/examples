%{
#include <stdio.h>
#define YYSTYPE char* 
#include "y.tab.h"
void debuglog(const char* x) {
}
%}

%% 
[0123456789]+ {yylval=(char*) yytext; debuglog("NUMBER\n");return NUMBER;}
[ \n\t\r]+    /**/
[\{] {yylval=(char*) yytext;  debuglog("LCBRACE\n");return LCBRACE; }
[\}] {yylval=(char*) yytext;  debuglog("RCBRACE\n");return RCBRACE; }
[A-Za-z_][A-Za-z0-9_]* {yylval=strdup(yytext);debuglog("WORD\n");return WORD;}
["] {yylval=(char*) yytext;  debuglog("QUOTE\n");return QUOTE; }
\[ {yylval=(char*) yytext;  debuglog("LSBRACE\n");return LSBRACE; }
= {yylval=(char*) yytext;  debuglog("EQUALS\n");return EQUALS; }
\] {yylval=(char*) yytext;  debuglog("RSBRACE\n");return RSBRACE; }
\[[01234567890]+\] {yylval=strdup(yytext);  debuglog("TAG\n");return TAG; }
%%
