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
	STMT,
	ST, LT, NS, NL, EQ,
	PARAMS,
	FUN,
	FUNCALL
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
Node* createArray(ArrayUnit *arr);

Node* createComplex(int op , Node* left, Node* right, Hash localvars);
Node* createIF(Node* expr, Node* thenstmt, Hash localvars);
Node* createFUN(Node* paramslist, Node* stmts, Hash localvars);
Node* createSTMTS(Node* stmt, Node* stmts, Hash localvars);
Node* createPARAMS(Node* param, Node* params);
Node* createPARAM(char* name, Hash localvars);
Node* createFUNCALL(Hash funHash, char* name, ArrayUnit* paramslist, Hash localvars);

Data ExPARAMS(Node* node, ArrayUnit* actualParams);

#endif   /* ----- #ifndef NODE_INC  ----- */
