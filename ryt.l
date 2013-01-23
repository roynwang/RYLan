/*should use such comment style*/
%{
	#include <stdio.h>

	#define LT 1
	#define LE 2
	#define EQ 3
	#define NE 4
	#define GT 5
	#define GE 6
	#define IF 7
	#define THEN 8
	#define ELSE 9 
	#define ID 10
	#define STRING 11
	#define NUM 12
%}

delim         [ \t\n]
ws            {delim}+
letter	      [A-Za-z]
digit         [0-9]
id            {letter}({letter}|{digit})*
number        {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
op            [-\+s\*\/\%]

%%

{ws}          {} 
if            {display("IF: ",yytext);}
then          {display("THEN: ",yytext);}
else          {display("ELSE: ",yytext);}
{id}          {display("ID: ",yytext);}
{number}      {display("NUM: ",yytext);} 
{op}          {display("OP: ",yytext);} 
"<"           {display("COMPARE",yytext);}
"="           {display("ASSIGN",yytext);}
.             {display("!!!!!!!!!!!!!!UNDEFINED: ", yytext);}    

%%
display(char* type, char* value){
	printf("%s ----- %s\n", type, value);
}


int main(){
	yylex();
	return 0;
}
