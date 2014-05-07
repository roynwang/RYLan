/*
 * =====================================================================================
 *
 *       Filename:  objmember.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/18/2013 10:06:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "objmembernode.h"

Node* createOBJFUN(const char* objname, const char* funname, Node* paramslist){
	Node* ret = createEmptyNode();
	ret->op = OBJFUN;
	//set the caller object
	if(objname!= NULL)
		ret->left = createVar(objname);
	//set the called function
	ret->right = createFUNCALL(funname, params);
	return ret;
}
Node* ExOBJFUN(Node* node){
	RuntimeEnv env;
	if(node->left != NULL){
		ObjectNode *on = getItem(node->env->varsenv,	node->left->data->value.strValue);
		env = on->env;
	}
}
Node* createOBJVAR(const char* objname, const char* varname, Node* paramslist){
	Node* ret = createEmptyNode();
	ret->op = OBJFUN;
	//set the caller object
	if(objname!= NULL)
		ret->left = createVar(objname);
	//set the called function
	ret->right = createVar(varname);
	return ret;
}

Node* createFUNCALL(const char* funname, Node* params){
	Node* ret = createEmptyNode();
	ret->op = FUNCALL;
	ret->left = params;
	ret->right = funname;
	return ret;
}


