CC = gcc
YACC = yacc
LEX = flex
PARSER = parser
HASH = GlobalHashTable
SYNTAX = SyntaxNode
OO = OONode
TEST = Test
DEBUG =  -g

prog: lex.yy.c node.o hash.o dataunit.o debug.o
	$(CC) lex.yy.c node.o hash.o dataunit.o debug.o -o $(PARSER) $(DEBUG)

lex.yy.c: ryt.l y.tab.c debug.h
	$(LEX) ryt.l

y.tab.c: ryt.y debug.h
	$(YACC) ryt.y


test: $(TEST)/hashtest.c dataunit.o node.o hash.o debug.o
	$(CC) $(TEST)/hashtest.c dataunit.o node.o hash.o debug.o -o StructureTest $(DEBUG)

dataunit.o: $(HASH)/dataunit.h $(HASH)/dataunit.c debug.h
	$(CC) -c $(HASH)/dataunit.h $(HASH)/dataunit.c debug.h $(DEBUG)

hash.o: $(HASH)/hash.h $(HASH)/hash.c debug.h
	$(CC) -c $(HASH)/hash.h $(HASH)/hash.c  debug.h $(DEBUG)

node.o: $(SYNTAX)/node.h $(SYNTAX)/node.c 
	$(CC) -c $(SYNTAX)/node.h $(SYNTAX)/node.c  $(DEBUG)

debug.o: debug.h debug.c
	$(CC) -c debug.h debug.c $(DEBUG)

oosupport: $(OO)/objectnode.h $(OO)/classnode.h $(OO)/objectnode.c
	$(CC) -c $(OO)/objectnode.h $(OO)/classnode.h $(OO)/objectnode.c

clean:
	rm *.o lex.yy.c y.tab.c *~ $(PARSER) StructureTest


