/*
 * =====================================================================================
 *
 *       Filename:  loopnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 09:39:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "loopnode.h"
#include "stmtnode.h"
#include "ifnode.h"
Node* createWHILE(Node* judge, Node* body){
	Node* stmts = createSTMT(body, NULL);
	Node* ret= createIF(judge, stmts);
	stmts->right = ret;
	return ret;
}
Node* createFOR(Node* initial, Node* judge, Node* step, Node* body){
	Node* whilestmt = createWHILE(judge, createSTMT(body,step));
	return createSTMT(initial, whilestmt);
}




