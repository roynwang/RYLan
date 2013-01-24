%{
#include <stdio.h>
typedef char* string;
#define YYSTYPE string
%}
%token VARNAME ASSIGN STRVALUE END
%%
file   : record file
	   | record
	   ;
record : VARNAME ASSIGN STRVALUE END     {printf("DECLARE: %s = %s  \n", $1,$3); }
	   ;
%%
int main(){
	yyparse();
	return 0;
}
int yyerror(char* msg){
		printf("Error encountered : %s\n", msg);
}
