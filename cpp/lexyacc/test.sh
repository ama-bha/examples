#!/bin/bash
rm a.out
lex t.l && yacc -d --verbose --debug  t.y && gcc lex.yy.c y.tab.c -lfl -ly
