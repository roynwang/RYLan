/*
 * =====================================================================================
 *
 *       Filename:  retnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:18:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "retnode.h"
Node* createRET(Node* value){
	Node* ret = createEmptyNode();
	debugmsg(CREATE,"create RET ... ... %p %p",ret, ret->ptrlocalvars);
	ret->op = RET;
	ret->left = value;
	return ret;
}

Data ExRET(Node* node){
	debugmsg(EXECUTE, "executing RET ... ... %p", node);
	Data ret = Ex(node->left);
	if(ret.valueType == VarType){
		Data* tmp = getbyName(ret.value.varValue, *(node->ptrglobalvars), *(node->ptrlocalvars));
		memcpy(&ret, tmp, sizeof(Data));
	}
	debugmsg(EXECUTE, "return ... ... %s", toString(&ret));
	return ret;
}


