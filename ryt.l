%{
#include "y.tab.c"  
#include <stdio.h>
#include <string.h>
%}
delim       [ \t\n]
ws          {delim}+
letter      [A-Za-z]
digit       [0-9]
assign      [=]
id          {letter}({letter}|{digit})*
strvalue    \"({letter}|{digit})*\"
end         ;

%%
{ws}              {}
{id}              { yylval = strdup(yytext); return VARNAME; }
{assign}          { return ASSIGN; }
{strvalue}        { yylval = strdup(yytext); return STRVALUE; }
{end}             { yylval = strdup(yytext); return END;}
%%
int yywrap()
{
		return 1;
}
