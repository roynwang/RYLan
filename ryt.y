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
%token  TOKENASSIGN  SEMC FUNDEF BLOCKSTART BLOCKEND RUN LP RP COMMA
%token <str>  symbol
%token <value> expr
%type  <node> stmt stmts param params fundef arrayexpr
%type <arrelem> arrayelement arrayelements
%%
prog           :  fundefs                                                  {printf("xxxxxx");}
               ;
fundefs        :  fundefs fundef                                           {}
               |  fundef                                                   {}
			   ;

fundef         :  FUNDEF symbol LP params RP BLOCKSTART stmts BLOCKEND    {$$ = createFUN($2,$4,$7,varshash,funshash);
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
stmts          :  stmts stmt                                              {$$ = createSTMTS($2,$1,varshash);}
               |  stmt                                                    {$$ = createSTMTS($1,NULL,varshash);}
			   ;
stmt           :  symbol TOKENASSIGN expr SEMC  /*var assign */           {$$ = createComplex(ASSIGN,createVar($1),createInt($3),varshash);}
			   |  symbol arrayexpr SEMC /*fun cal*/                       {$$ = createFUNCALL(funshash,$1,$2,varshash);}
               ;
arrayexpr      :  LP arrayelements RP                                     {$$ = createArray($2);}
               ;
arrayelements  :  arrayelement COMMA arrayelements                        {$1->next = $3; $$ = $1;}
               |  arrayelement                                            {$$ = $1;}
			   |                                                          {$$ = NULL;}
			   ;
arrayelement   :  symbol                                                  {Data* tmp = createPtrData(getItem(*varshash,$1));$$ = createArrayUnit(tmp);}
               |  expr                                                    {$$ = createArrayUnit(createIntData($1));}
			   ;

%%

void execute(){
	printf("Executing function \n");
}
int main(){	
	mtrace();
	varshash = (Hash*)malloc(sizeof(Hash*));
	funshash = (Hash*)malloc(sizeof(Hash*));
	*varshash = initHash(65536);
	*funshash  = initHash(65536);
	printf("global vars = %p funcs = %p\n", varshash, funshash);
    printf("YACC started\n");
	yyparse();
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

