%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SyntaxNode/node.h"
#include "GlobalHashTable/hash.h"
#include "debug.h"
#define MAIN "main"
void  yyerror(char*s);
void* cur = NULL;
char* curFun = NULL;
Hash* varshash = NULL;
Hash* funshash = NULL;
Node* funnode = NULL;
Node* mainfunc = NULL;
%}
%union {
	char* str;
	int value;
	Node *node;
	ArrayUnit *arrelem;
}
%token SEMC FUNDEF BLOCKSTART BLOCKEND RUN LP RP COMMA PRINT WHILELOOP IFSTMT ELSESTMT FORLOOP

%right TOKENASSIGN    /*less priority than calculate OP*/ 
%left OPADD OPST
%token <str>  symbol strvalue
%token <value> intvalue
%type  <node> stmt stmts param params fundef arrayexpr expr stmtsblock whileloop forstmt
%type  <arrelem> arrayelement arrayelements
%%
prog           :  fundefs                                                  {}
               ;
fundefs        :  fundefs fundef                                           {}
               |  fundef                                                   {}
			   ;

fundef         :  FUNDEF symbol LP params RP stmtsblock                   {$$ = createFUN($2,$4,$6,varshash,funshash);
if(strcmp(MAIN,$2)==0) mainfunc = $$;
else funnode = $$;
}
               ;

params         :  param  COMMA params                                     {$$ = createPARAMS($1,$3);}
			   |  param                                                   {$$ = $1;}
			   |                                                          {$$ = NULL;}
               ;

param          :  symbol                                                  {$$ = createPARAM($1,varshash);}
               ;

stmtsblock     :  BLOCKSTART stmts BLOCKEND                               {$$ = $2;}
               |  stmt                                                    {$$ = $1;}
               ;

stmts          :  stmt stmts                                              {$$ = createSTMTS($1,$2,varshash);}
               |  stmt                                                    {$$ = createSTMTS($1,NULL,varshash);}
			   ;

stmt		   :  expr SEMC                                               {$$ = $1;}
               |  whileloop                                               {$$ = $1;}

			   |  forstmt                                                 {$$ = $1;}
			   ;
whileloop      :  WHILELOOP LP expr RP stmtsblock                         {$$ = createWHILE($3,$5,varshash);}
               ;

forstmt        :  FORLOOP LP  expr SEMC expr SEMC expr RP stmtsblock       {$$ = createFOR($3, $5, $7, $9, varshash);}
               ;

arrayexpr      :  LP arrayelements RP                                     {$$ = createArray($2);}
               ;
arrayelements  :  arrayelement COMMA arrayelements                        {$1->next = $3; $$ = $1;}
               |  arrayelement                                            {$$ = $1;}
			   |                                                          {$$ = NULL;}
			   ;
arrayelement   :  symbol                                                  {Data* tmp = createVarData($1);$$ = createArrayUnit(tmp);}
               |  intvalue                                                {$$ = createArrayUnit(createIntData($1));}
			   ;
expr           :  intvalue                                                {$$ = createInt($1);} 
			   |  symbol TOKENASSIGN expr       /*var assign */           {$$ = createComplex(ASSIGN,createVar($1), $3,varshash);}
               |  symbol                                                  {$$ = createVar($1);}
               |  expr OPADD expr                                         {$$ = createComplex(ADD,$1,$3,varshash);}
			   |  expr OPST expr                                          {$$ = createComplex(ST, $1,$3,varshash);}
			   |  PRINT LP symbol RP 		                              {$$ = createDISPLAY(createVar($3),varshash);}
               |  symbol arrayexpr /*fun cal*/                             {$$ = createFUNCALL(funshash,$1,$2,varshash);}
               ;  
%%

int main(){	
	mtrace();
    debugmsg(YACC, "START YACC ... ...");
	varshash = (Hash*)malloc(sizeof(Hash*));
	funshash = (Hash*)malloc(sizeof(Hash*));
	//create node of print function
	*varshash = initHash(65536);
	*funshash  = initHash(65536);
	debugmsg(YACC,"global vars = %p funcs = %p", varshash, funshash);
    printf("YACC started\n");
	yyparse();
	printf("---------------------MAIN--------------------\n");
	Ex(mainfunc);
	printf("---------------------DONE--------------------\n");
	freeNode(funnode);
	if(mainfunc!=NULL){
		freeNode(mainfunc);
	}
	freeHash(*varshash);
	freeHash(*funshash);
	free(varshash);
	free(funshash);
	yy_delete_buffer(YY_CURRENT_BUFFER);
	yy_init = 1;
	return 0;
}
void yyerror(char *s) { 
	fprintf(stdout, "%s\n", s); 
	freeNode(funnode);
	freeHash(*varshash);
	freeHash(*funshash);
	free(varshash);
	free(funshash);
}

