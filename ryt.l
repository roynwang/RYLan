%{
#include "y.tab.c"
#include <string.h>
#include "debug.h"

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
{ws}              { }
"."               { debugmsg(LEX,"DOT");return DOT;}
"def"             { debugmsg(LEX,"DEF");return DEF;}
"class"           { debugmsg(LEX,"CLASS");return CLASS;}

"return"          { debugmsg(LEX,"RETURN"); return RETURN;}
"<"               { debugmsg(LEX,"<");return OPST;}
"while"           { debugmsg(LEX,"WHILELOOP");return WHILELOOP;}
"if"              { debugmsg(LEX,"IFSTMT"); return IFSTMT;}
"else"            { debugmsg(LEX,"ELSESTMT"); return ELSESTMT;}
"for"             { debugmsg(LEX,"FORLOOP"); return FORLOOP;}
"print"           { debugmsg(LEX,"PRINT");return PRINT;}
{id}              { yylval.str =strdup(yytext);debugmsg(LEX,"symbol = %s", yylval.str);return symbol;}
{assign}          { debugmsg(LEX,"ASSIGN");return TOKENASSIGN;}
{end}             { debugmsg(LEX,";");return SEMC;}
{number}          { yylval.value = atoi(yytext);debugmsg(LEX,"number = %d", yylval.value);return intvalue; }
"{"               { debugmsg(LEX,"BLOCKSTART"); return BLOCKSTART;}
"}"               { debugmsg(LEX,"BLOCKEND");return BLOCKEND;}
"("               { debugmsg(LEX,"(");return LP;}
")"               { debugmsg(LEX,")");return RP;}
","               { debugmsg(LEX,",");return COMMA;}
"+"               { debugmsg(LEX,"+");return OPADD;}

%%
int yywrap()
{
		return 1;
}

