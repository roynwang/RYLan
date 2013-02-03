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
	FUNCALL,
	DISPLAY
}OpEnum;
typedef struct _Node{
	int op;
	char ismarkedforfree;
	struct _Node* left;
	struct _Node* right;
	Data* data;
	Hash* ptrlocalvars;
	Hash* ptrfuncs;
}Node;

Data Ex(Node* node);
void freeNode(Node* node);
Node* createVar(char* name);
Node* createStr(char* value);
Node* createInt(int value);
Node* createArray(ArrayUnit *arr);

Node* createComplex(int op , Node* left, Node* right, Hash *ptrlocalvars);
Node* createIF(Node* expr, Node* thenstmt, Hash *ptrlocalvars);
Node* createFUN(char* name, Node* paramslist, Node* stmts, Hash *ptrlocalvars, Hash *ptrfunhash);
Node* createSTMTS(Node* stmt, Node* stmts, Hash *ptrlocalvars);
Node* createPARAMS(Node* param, Node* params);
Node* createPARAM(char* name, Hash *ptrlocalvars);
Node* createFUNCALL(Hash *funHash, char* name, Node* paramslist, Hash *ptrlocalvars);
Node* createDISPLAY(Node* value, Hash* ptrlocalvars);
Node* createEXPR(Node* node, Hash* ptrlocalvars);
Node* createWHILE(Node* judge, Node* body, Hash *ptrlocalvars);

Data ExPARAMS(Node* node, ArrayUnit* actualParams);

#endif   /* ----- #ifndef NODE_INC  ----- */
