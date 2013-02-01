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
strvalue    \"({letter}|{digit})*\
end         ;
number      {digit}+
fun         fun


%%
{ws}              {}
"run"             { debugmsg("RUN");}
"fun"             { debugmsg("FUN");return FUNDEF;}
{id}              { yylval.str =strdup(yytext);debugmsg(yytext);return symbol;}
{assign}          { return TOKENASSIGN;}
{end}             { return SEMC;}
{number}          { yylval.value = atoi(yytext); debugmsg(yytext); return expr; }
"{"               { debugmsg("BLOCKSTART"); return BLOCKSTART;}
"}"               { debugmsg("BLOCKEND");return BLOCKEND;}
"("               { debugmsg("LP");return LP;}
")"               { debugmsg("RP");return RP;}
","               { return COMMA;}

%%
int yywrap()
{
		return 1;
}
void debugmsg(char* msg){
		printf("[LEX] %s\n", msg);
}

