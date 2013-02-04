/*
 * =====================================================================================
 *
 *       Filename:  debug.c *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/04/2013 11:09:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "debug.h"
void debugmsg(int level, char* fmt, ...){

	char buffer[100];
	*buffer = '\0';

	va_list argptr;
	va_start(argptr, fmt);
	vsprintf(buffer, fmt, argptr);
	va_end(argptr);

	char* str = "[NONE]";
	switch(level & DEBUGLEVEL){
		case LEX:
			str = "1 [LEX]";
			break;
		case YACC:
			str = "2 [YACC]";
			break;
		case DATASTRUCTURE:
			str = "3 [DATASTRUCTURE]";
			break;
		case CREATE:
			str = "4 [CREATE]";
			break;
		case EXECUTE:
			str = "5 [EXECUTE]";
			break;
		case FREE:
			str = "6 [FREE]";
			break;
	}
	printf("%s: %s\n", str, buffer);
}

