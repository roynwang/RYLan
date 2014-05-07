/*
 * =====================================================================================
 *
 *       Filename:  node.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/28/2013 09:43:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  NODE_INC
#define  NODE_INC

#include "../GlobalHashTable/dataunit.h"
#include "../GlobalHashTable/hash.h"
#include "../debug.h"
typedef enum { 
	NONE,
	ASSIGN, GET,
	ADD, SUB, MUL,DIV, 
	IF, 
	NOT,
	STMT,
	ST, LT, NS, NL, EQ,
	PARAMS,
	FUN,FUNCALL,
	OBJFUN, OBJVAR,
	DISPLAY,
	RET,
}OpEnum;
typedef struct {
	Hash* varsenv;
	Hash* funsenv;
}RuntimeEnv;
typedef struct _Node{
	int op;
	char ismarkedforfree;
	struct _Node* left;
	struct _Node* right;
	Data* data;
	RuntimeEnv* env;
}Node;


Data Ex(Node* node);
Node* createEmptyNode();
Data* getbyName(char* name, Hash globalhash, Hash localhash);

#endif   /* ----- #ifndef NODE_INC  ----- */
