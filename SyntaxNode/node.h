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
typedef enum { 
	NONE,
	ASSIGN, GET,
	ADD, SUB, MUL,DIV, 
	IF, 
	NOT,
	EXE,
	ST
}OpEnum;
typedef struct _Node{
	int op;
	struct _Node* left;
	struct _Node* right;
	Data* data;
	Hash localvars;
}Node;

Data Ex(Node* node);
void freeNode(Node* node);
Node* createVar(char* name);
Node* createStr(char* value);
Node* createInt(int value);

Node* createComplex(int op , Node* left, Node* right, Hash localvars);
Node* createIF(Node* expr, Node* thenstmt, Hash localvars);

#endif   /* ----- #ifndef NODE_INC  ----- */
