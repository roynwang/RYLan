%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SyntaxNode/node.h"
#include "GlobalHashTable/hash.h"
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
%token  TOKENASSIGN  SEMC FUNDEF BLOCKSTART BLOCKEND RUN LP RP COMMA PRINT
%left OPADD
%token <str>  symbol strvalue
%token <value> intvalue
%type  <node> stmt stmts param params fundef arrayexpr expr stmtsblock
%type  <arrelem> arrayelement arrayelements
%%
prog           :  fundefs                                                  {printf("xxxxxx");}
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
			   |                                                          {printf("NO params"); $$ = NULL;}
               ;

param          :  symbol                                                  {$$ = createPARAM($1,varshash);}
               ;

stmtsblock     :  BLOCKSTART stmts BLOCKEND                               {$$ = $2;}
               ;

stmts          :  stmt stmts                                              {$$ = createSTMTS($1,$2,varshash);}
               |  stmt                                                    {$$ = createSTMTS($1,NULL,varshash);}
			   ;
stmt           :  symbol TOKENASSIGN expr SEMC  /*var assign */           {$$ = createComplex(ASSIGN,createVar($1), $3,varshash);}
			   |  symbol arrayexpr SEMC /*fun cal*/                       {$$ = createFUNCALL(funshash,$1,$2,varshash);}
			   |  PRINT LP symbol RP SEMC                                 {$$ = createDISPLAY(createVar($3),varshash);}
               ;
arrayexpr      :  LP arrayelements RP                                     { printf("!!!!array %p\n", $2);$$ = createArray($2);}
               ;
arrayelements  :  arrayelement COMMA arrayelements                        {$1->next = $3; $$ = $1;}
               |  arrayelement                                            {$$ = $1;
			   printf("only 1 actual param\n");}
			   |                                                          {$$ = NULL;}
			   ;
arrayelement   :  symbol                                                  {Data* tmp = createVarData($1);$$ = createArrayUnit(tmp);printf("tmp = %p value = %p\n", tmp, tmp->value.varValue);}
               |  intvalue                                                {$$ = createArrayUnit(createIntData($1));}
			   ;
expr           :  intvalue                                                {$$ = createInt($1);} 
               |  symbol                                                  {$$ = createVar($1);}
               |  expr OPADD expr                                         {$$ = createComplex(ADD,$1,$3,varshash);}
               ;

%%

void execute(){
	printf("Executing function \n");
}
int main(){	
	mtrace();
	varshash = (Hash*)malloc(sizeof(Hash*));
	funshash = (Hash*)malloc(sizeof(Hash*));
	//create node of print function
	*varshash = initHash(65536);
	*funshash  = initHash(65536);
	printf("global vars = %p funcs = %p\n", varshash, funshash);
    printf("YACC started\n");
	yyparse();
	printf("---------------------MAIN--------------------\n");
	Ex(mainfunc);
	printf("---------------------DONE--------------------\n");
	freeNode(funnode);
	if(mainfunc!=NULL){
		printf("free MAIN 1!!!!!!!!!!!\n");
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
	printf("xxxxxxxxxxxxxxxxxxx\n");
	fprintf(stdout, "%s\n", s); 
	freeNode(funnode);
	freeHash(*varshash);
	freeHash(*funshash);
	free(varshash);
	free(funshash);
}

