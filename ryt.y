%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SyntaxNode/node.h"
void  yyerror(char*s);
void* cur = NULL;
char* curFun = NULL;
Hash* varshash = NULL;
Hash* funshash = NULL;
Node* funnode = NULL;

%}
%union {
	char* str;
	int value;
	Node *node;
}
%token  TOKENASSIGN  SEMC FUNDEF BLOCKSTART BLOCKEND RUN LP RP COMMA
%token <str>  symbol
%token <value> expr
%type  <node> stmt stmts param params fundef
%%
prog           :  fundef                                                  {printf("xxxxxx");
 funnode = $1;
}
               ;

fundef         :  FUNDEF symbol LP params RP BLOCKSTART stmts BLOCKEND    {$$ = createFUN($2,$4,$7,varshash,funshash);}
               ;
params         :  param  COMMA params                                     {$$ = createPARAMS($1,$3);}
			   |  param                                                   {$$ = $1;}
               ;
param          :  symbol                                                  {$$ = createPARAM($1,varshash);}
               ;
stmts          :  stmts stmt                                              {$$ = createSTMTS($2,$1,varshash);}
               |  stmt                                                    {$$ = createSTMTS($1,NULL,varshash);}
			   ;
stmt           :  symbol TOKENASSIGN expr SEMC                            {$$ = createComplex(ASSIGN,createVar($1),createInt($3),varshash);}
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

