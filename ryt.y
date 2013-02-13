%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SyntaxNode/node.h"
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
%token SEMC DEF BLOCKSTART BLOCKEND RUN LP RP COMMA PRINT WHILELOOP IFSTMT ELSESTMT FORLOOP RETURN CLASS DOT
%right TOKENASSIGN    /*less priority than calculate OP*/ 
%left OPADD OPST
%token <str>  symbol strvalue
%token <value> intvalue
%type  <node> stmt stmts param params fundef arrayexpr expr stmtsblock whileloop forstmt returnstmt classdefs classdef classbody classelements classelement vardef simpleexpr objvar objcall
%type  <arrelem> arrayelement arrayelements
%%
scope          :  classdefs                                                {}
               ;
classdefs      :  classdefs classdef                                       {}
               |  classdef                                                 {}
			   ;
classdef       :  DEF CLASS symbol classbody                               {registerclass($3,*ptrclasstable,curclass); curclass = createClassNode(NULL);}
               ;
classbody      :  BLOCKSTART classelements BLOCKEND                        {}
               ;
classelements  :  classelements classelement                               {/*nothing*/} |  classelement                                             {/*nothing*/}
			   ;

classelement   :  fundef                                                   {}
               |  vardef                                                   {/*register the var*/}
			   ;
vardef         :  DEF symbol SEMC                                          { registervar($2, &EMPTY,curclass);  }
			   ;
			   
fundef         :  DEF symbol LP params RP stmtsblock                       { $$ = createFUN($2,$4,$6, curclass->vartable,curclass->funtable);
  registerfun($2,$$, curclass);
}
               ;

params         :  param  COMMA params                                     {$$ = createPARAMS($1,$3);}
			   |  param                                                   {$$ = $1;}
			   |                                                          {$$ = NULL;}
               ;

param          :  symbol                                                  {$$ = createPARAM($1,curclass->vartable);}
               ;

stmtsblock     :  BLOCKSTART stmts BLOCKEND                               {$$ = $2;}
               |  stmt                                                    {$$ = $1;}
               ;

stmts          :  stmt stmts                                              {$$ = createSTMTS($1,$2,curclass->vartable);}
               |  stmt                                                    {$$ = createSTMTS($1,NULL, curclass->vartable);}
			   ;

stmt		   :  expr SEMC                                               {$$ = $1;}
               |  objcall SEMC                                            {$$ = $1;}
               |  returnstmt                                              {$$ = $1;}
               |  whileloop                                               {$$ = $1;}

			   |  forstmt                                                 {$$ = $1;}
			   ;
returnstmt     :  RETURN expr SEMC                                        {$$ = createRET($2,curclass->vartable);}

whileloop      :  WHILELOOP LP expr RP stmtsblock                         {$$ = createWHILE($3,$5,curclass->vartable);}
               ;

forstmt        :  FORLOOP LP  expr SEMC expr SEMC expr RP stmtsblock      {$$ = createFOR($3, $5, $7, $9, curclass->vartable);}
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
               |  objvar                                                  {$$ = $1;}
               |  objcall                                                 {$$ = $1;  /*cause conflicts!!!!!!!!!!!*/}
			   |  symbol TOKENASSIGN expr       /*var assign */           {$$ = createComplex(ASSIGN,createVar($1), $3,curclass->vartable);}
               |  symbol                                                  {$$ = createVar($1);}
               |  expr OPADD expr                                         {$$ = createComplex(ADD,$1,$3,curclass->vartable);}
			   |  expr OPST expr                                          {$$ = createComplex(ST, $1,$3,curclass->vartable);}
			   |  PRINT LP symbol RP 		                              {$$ = createDISPLAY(createVar($3),curclass->vartable);}
               |  symbol arrayexpr /*fun cal*/                            {$$ = createFUNCALL(curclass->funtable,$1,$2,curclass->vartable);}
               ;  
simpleexpr     :  intvalue                                                {$$ = createInt($1);}
               |  strvalue                                                {$$ = createStr($1);} 
			   ;
objvar         :  symbol DOT symbol                                       {$$ = createOBJVAR($1,$3,curclass->vartable);}
			   ;
objcall        :  symbol DOT symbol arrayexpr                             {$$ = createOBJFUN($1,$3,$4,curclass->vartable);}

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

