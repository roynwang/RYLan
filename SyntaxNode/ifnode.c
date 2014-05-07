/*
 * ===================================================================================== *
 *       Filename:  ifnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 09:45:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "ifnode.h"
#include "logicnode.h"

Node* createIF(Node* expr, Node* thenstmt){
	Node* ret = createEmptyNode();
	debugmsg(CREATE, "creating if ... ... %p", ret );
	ret->op =  IF;
	ret->left = expr;
	ret->right = thenstmt;
	return ret;
}
Data ExIF(Node* node){
	Data l = Ex(node->left);
	debugmsg (EXECUTE, "executing if ... ..." );
	if(isTrue(&l)){
		debugmsg (EXECUTE, "TRUE ... ..." );
		Ex(node->right);
		return TRUE;
	}
	return FALSE;
}
Node* createIFELSE(Node* expr, Node* thenstmt, Node* elsestmt){
	Node* ret = createEmptyNode();
	ret->op =  IF;
	ret->left = createNOT(createIF(expr, thenstmt));
	ret->right = elsestmt;
	return ret;
}


