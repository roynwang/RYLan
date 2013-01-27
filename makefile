CC = gcc
YACC = yacc
LEX = flex
PARSER = parser

prog: lex.yy.c utility.o
	$(CC) lex.yy.c utility.o -o $(PARSER)

lex.yy.c: ryt.l y.tab.c
	$(LEX) ryt.l

y.tab.c: ryt.y
	$(YACC) ryt.y

utility.o: utility.h utility.c
	$(CC) -c utility.h utility.c

clean:
	rm utility.o lex.yy.c y.tab.c *~ $(PARSER) 




