CC = gcc
YACC = yacc
LEX = flex
PARSER = parser
HASH = GlobalHashTable
SYNTAX = SyntaxNode
TEST = Test
DEBUG =  -g

prog: lex.yy.c node.o hash.o dataunit.o
	$(CC) lex.yy.c node.o hash.o dataunit.o -o $(PARSER) $(DEBUG)

lex.yy.c: ryt.l y.tab.c
	$(LEX) ryt.l

y.tab.c: ryt.y
	$(YACC) ryt.y

utility.o: utility.h utility.c
	$(CC) -c utility.h utility.c


test: $(TEST)/hashtest.c dataunit.o node.o hash.o
	$(CC) $(TEST)/hashtest.c dataunit.o node.o hash.o -o StructureTest $(DEBUG)

dataunit.o: $(HASH)/dataunit.h $(HASH)/dataunit.c
	$(CC) -c $(HASH)/dataunit.h $(HASH)/dataunit.c $(DEBUG)

hash.o: $(HASH)/hash.h $(HASH)/hash.c
	$(CC) -c $(HASH)/hash.h $(HASH)/hash.c  $(DEBUG)

node.o: $(SYNTAX)/node.h $(SYNTAX)/node.c
	$(CC) -c $(SYNTAX)/node.h $(SYNTAX)/node.c  $(DEBUG)



clean:
	rm *.o lex.yy.c y.tab.c *~ $(PARSER) StructureTest


