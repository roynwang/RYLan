/*
 * =====================================================================================
 *
 *       Filename:  stmtnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 09:18:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "stmtnode.h"

Node* createSTMT(Node* stmt, Node* stmts){
	Node* ret = createEmptyNode();
	debugmsg(CREATE,"creating stmts ... ...%p", ret);
	ret->op =  STMT;
	ret->left = stmt;
	ret->right = stmts;
	return ret;
}

Data ExSTMT(Node* node, RuntimeEnv *env){
	Data left = Ex(node->left);
	Data right = Ex(node->right);
	return right.valueType == EMPTY.valueType  ? left : right;
}

