%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
Node* fun;

Node* installSymbolAssign(char* id, int exp);
Node* installFun(char* id, Node* body);
void  execute();
void  yyerror(char*s);

void* cur = NULL;
char* curFun;

%}
%union {
	char* str;
	int value;
	Node *node; /* 结点地址 */
}
%token  ASSIGN  SEMC FUN BLOCKSTART BLOCKEND RUN
%token <str>  symbol
%token <value> expr
%type  <node> stmtlist stmt
%%
prog           :   fundefs RUN SEMC                                       { execute();}
               ;

fundefs        :   fundefs fundef
               |   fundef 
			   ;

fundef         :   FUN symbol BLOCKSTART stmtlist BLOCKEND                {printf("fundef: %s \n", $2);
                                                                           installFun($2, $4);
                                                                          }
               ;
stmtlist       :   stmtlist stmt                                          {printf("!!!!!!!statement\n");}

               |   stmt                                                   {}
               ;
stmt           :   symbol ASSIGN expr SEMC                                {printf("add stmt: ASSIGN %s \n", $1);
                                                                           $$ = installSymbolAssign($1,$3);
			   }
			   ;
%%

Node* installSymbolAssign(char* id, int exp){
	printf("install symbol assign --- %s %d\n", id, exp);
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->varName = id;
	ret->op = AssignOp;
	ret->intValue = exp;
	return ret;
}
Node* installFun(char* id, Node* body){
	printf("install function  %s: %p\n", id, body);
	fun = body;
}
void execute(){
	printf("Executing function %p \n", fun);
	ex(fun);
}
int main(){
	yyparse();
	return 0;
}
void yyerror(char *s) { 
	    fprintf(stdout, "%s\n", s); 
}

