/*
 * =====================================================================================
 *
 *       Filename:  utility.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/26/2013 12:26:49 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#define LEXDEBUG 1
#define YACCDEBUG 2
typedef enum {NONE, AssignOP} opEnum;
typedef struct _exUnit{
	char* cName;
	opEnum op;
	int iValue;
	struct _exUnit* next;
} Node;
int VarList[256];
int DEBUG = 3;

void ex(Node* node);
