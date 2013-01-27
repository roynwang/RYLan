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
typedef enum {NONE, AssignOp, AddOp} opEnum;
typedef struct _exUnit{
	char* varName;
	int intValue;
	opEnum op;
	struct _exUnit* next;
	int ret;
} Node;
int VarList[256];
int DEBUG;

int ex(Node* node);
