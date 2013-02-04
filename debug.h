/*
 * =====================================================================================
 *
 *       Filename:  debug.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/04/2013 11:08:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  DEBUG_INC
#define  DEBUG_INC
#define DEBUGLEVEL 60

#include <stdarg.h>
typedef enum{
	LEX = 1,  YACC= 2, DATASTRUCTURE = 4, EXECUTE = 8, FREE = 16, CREATE = 32
}loglevel;

void debugmsg(int level, char* fmt, ...);

#endif   /* ----- #ifndef DEBUG_INC  ----- */
