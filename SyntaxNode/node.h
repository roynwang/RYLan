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
#include "../GlobalHashTable/dataunit.h"
#include "../GlobalHashTable/hash.h"
typedef enum { 
	ASSIGN, GET, ADD, SUB, MUL,DIV
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
