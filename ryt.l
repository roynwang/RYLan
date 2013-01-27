%{
#include "y.tab.c"  
#include <stdio.h>
#include <string.h>

void debugmsg(char* msg);
%}

delim       [ \t\n]
ws          {delim}+
letter      [A-Za-z]
digit       [0-9]
assign      =
id          {letter}({letter}|{digit})*
strvalue    \"({letter}|{digit})*\"
end         ;
number      {digit}+
fun         fun

%%
{ws}              {}
"run"             { debugmsg("RUN"); return RUN;}
"fun"             { debugmsg("FUN"); return FUN;}
{id}              { yylval.str = strdup(yytext); debugmsg(yytext); return symbol; }
{assign}          { return ASSIGN; }
{end}             { return SEMC;}
{number}          { yylval.value = atoi(yytext); debugmsg(yytext); return expr;}
"{"               { return BLOCKSTART;}
"}"               { return BLOCKEND;}
%%
int yywrap()
{
		return 1;
}
void debugmsg(char* msg){
	if(DEBUG & LEXDEBUG)
		printf("[LEX] %s\n", msg);
}
