CC = gcc
YACC = yacc
LEX = flex
PARSER = parser
HASH = GlobalHashTable
SYNTAX = SyntaxNode
TEST = Test

prog: lex.yy.c utility.o
	$(CC) lex.yy.c utility.o -o $(PARSER)

lex.yy.c: ryt.l y.tab.c
	$(LEX) ryt.l

y.tab.c: ryt.y
	$(YACC) ryt.y

utility.o: utility.h utility.c
	$(CC) -c utility.h utility.c


test: $(TEST)/hashtest.c dataunit.o node.o hash.o
	$(CC) $(TEST)/hashtest.c dataunit.o node.o hash.o -o ParserTest

dataunit.o: hash.o $(HASH)/dataunit.h $(HASH)/dataunit.c
	$(CC) -c $(HASH)/dataunit.h $(HASH)/dataunit.c hash.o

hash.o: $(HASH)/hash.h $(HASH)/hash.c
	$(CC) -c $(HASH)/hash.h $(HASH)/hash.c 

node.o: $(SYNTAX)/node.h $(SYNTAX)/node.c
	$(CC) -c $(SYNTAX)/node.h $(SYNTAX)/node.c



clean:
	rm *.o lex.yy.c y.tab.c *~ $(PARSER)  ParserTest


