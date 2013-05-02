%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SyntaxNode/syntaxnode.h"
#include "GlobalHashTable/hash.h"
#include "OONode/classnode.h"
#include "debug.h"
#include "GC/gc.h"
#include "globdef.h"
#define MAIN "main"
void  yyerror(char*s);
//curFun = NULL;
//ptrclasstable = NULL;
//mainfunc = NULL;
//curclass = NULL;
%}
%union {
	char* str;
	int value;
	Node *node;
	ArrayUnit *arrelem;
}
%token SEMC DEF BLOCKSTART BLOCKEND RUN LP RP COMMA PRINT WHILELOOP IFSTMT ELSESTMT FORLOOP RETURN CLASS DOT LR RR
%right TOKENASSIGN    /*less priority than calculate OP*/ 
%left OPADD OPST
%token <str>  symbol strvalue
%token <value> intvalue
%type  <node> stmt stmts param params fundef arrayexpr expr stmtsblock whileloop forstmt returnstmt classdefs classdef classbody defs def vardef simpleexpr funcallexpr
%type  <arrelem> arrayelement arrayelements
%%
scope          :  classdefs                                                {}
               ;
classdefs      :  classdefs classdef                                       {}
               |  classdef                                                 {}
			   ;
classdef       :  DEF CLASS symbol classbody                               {}
               ;
classbody      :  BLOCKSTART defs BLOCKEND                                 {}
               ;
defs           :  defs def                                                 {/*nothing*/}
               |  def                                                      {/*nothing*/}
			   ;

def            :  fundef                                                   {}
               |  vardef                                                   {/*register the var*/}
			   ;
vardef         :  DEF symbol SEMC                                          { }
			   ;
			   
fundef         :  DEF symbol LP params RP stmtsblock                       { $$ = createFUN($2,$4,$6);
}
               ;

params         :  param  COMMA params                                     {$$ = createPARAMS($1,$3);}
			   |  param                                                   {$$ = $1;}
			   |                                                          {$$ = NULL;}
               ;

param          :  symbol                                                  {$$ = createPARAM($1);}
               ;

stmtsblock     :  BLOCKSTART stmts BLOCKEND                               {$$ = $2;}
               |  stmt                                                    {$$ = $1;}
               ;

stmts          :  stmt stmts                                              {$$ = createSTMT($1,$2);}
               |  stmt                                                    {$$ = createSTMT($1,NULL);}
			   ;

stmt		   :  expr SEMC                                               {$$ = $1;}
               |  returnstmt                                              {$$ = $1;}
               |  whileloop                                               {$$ = $1;}
			   |  forstmt                                                 {$$ = $1;}
			   ;
returnstmt     :  RETURN expr SEMC                                        {$$ = createRET($2);}
               ;

whileloop      :  WHILELOOP LP expr RP stmtsblock                         {$$ = createWHILE($3,$5);}
               ;

forstmt        :  FORLOOP LP  expr SEMC expr SEMC expr RP stmtsblock      {$$ = createFOR($3, $5, $7, $9);}
               ;
funcallexpr    :  symbol DOT symbol arrayexpr                             {}
               |  symbol arrayexpr
			   ;

arrayexpr      :  LP arrayelements RP                                     {$$ = createArray($2);}
               ;
arrayelements  :  arrayelement COMMA arrayelements                        {$1->next = $3; $$ = $1;}
               |  arrayelement                                            {$$ = $1;}
			   |                                                          {$$ = NULL; printf("!!!!!!!!!EMPTY ARRAY!!!!!!!!!!\n");}
			   ;
arrayelement   :  symbol                                                  {Data* tmp = createVarData($1);$$ = createArrayUnit(tmp);}
               |  intvalue                                                {$$ = createArrayUnit(createIntData($1));}
			   ;
expr           :  simpleexpr                                              {$$ = $1;} 
               |  symbol                                                  {$$ = createVar($1);}
			   |  PRINT LP symbol RP 		                              {$$ = createDISPLAY(createVar($3));}
               |  funcallexpr /*fun cal*/                                 {$$ = $1;}
               ;  

simpleexpr     :  intvalue                                                {$$ = createInt($1);}
               |  strvalue                                                {$$ = createStr($1);} 
			   ;
%%

int main(){	
    mtrace();

	initialGC();

	Hash classhash = initHash(HASHSIZE);
	ptrclasstable = &classhash;
	curclass = createClassNode(NULL);

    debugmsg(YACC, "START YACC ... ...");
	//create node of print function
	yyparse();
	printf("---------------------MAIN--------------------\n");
	ClassNode* mainclass = getItem(classhash,"MAIN");
	printf("mainclass  = %p \n", mainclass);
    printf("ptrclasstable ... ... %p\n", ptrclasstable);
	Node* mainfun = getfunmember("main", mainclass);
	setClassHash(ptrclasstable);
	Data t = Ex(mainfun);
	printf("---------------------DONE--------------------\n");

    finializeMem();

	yy_delete_buffer(YY_CURRENT_BUFFER);
	yy_init = 1;
	return 0;
}
void yyerror(char *s) { 
	fprintf(stdout, "%s\n", s); 
	printf("finialize syntax tree ... ...");
    finializeMem();
	printf("done\n");
}

