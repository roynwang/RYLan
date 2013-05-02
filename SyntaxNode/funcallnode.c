/*
 * =====================================================================================
 *
 *       Filename:  funcallnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 10:06:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
====================================================================
 */
#include <stdlib.h>
#include "funcallnode.h"
#include "simplenode.h"
#include "../OONode/objectnode.h"


Node* createFUNCALL(const char* objname, const char* funname, Node* paramslist){
	Node* ret = createEmptyNode();
	ret->op = FUNCALL;
	//set the caller object
	if(objname!= NULL)
		ret->left = createVar(objname);
	//set the called function
	ret->right = createCALLTAR(funname, params);
	return ret;
}
Node* createCALLTAR(const char* funname, Node* params){
	Node* ret = createEmptyNode();
	ret->op = CALLTAR;
	ret->left = params;
	ret->right = funname;
	return ret;
}
Data ExFUNCALL(Node* node){
}


Data ExFUN(Node* node){
	debugmsg(EXECUTE, "executing OBJFUN ... ... %p left = %p right = %p", node, node->left, node->right);
	Node* funexp = node->right;
	debugmsg(EXECUTE, "get OBJFUN info ... ... %p", funexp);

	Data objname = Ex(funexp->left);
	Data funname = Ex(funexp->right);
	ObjectNode* obj;

	//create new empty object when calling constructor 
	if( strcmp(funname.value.strValue, "new") == 0){
		obj = createObject(objname.value.strValue, NULL);
	}
	else{
		debugmsg(EXECUTE, "objname = %s ... ... funname = %s ", objname.value.strValue, funname.value.strValue);
		Data* ptrobj = getbyName(objname.value.strValue,*(node->ptrglobalvars), *(node->ptrlocalvars));
		obj = (ObjectNode*)ptrobj->value.ptrValue;
	}
	ClassNode* class = obj->type;
	Node * fun = getfunmember(funname.value.strValue, class);
	debugmsg(EXECUTE,"queried  obj fun ... ..%p left = %p right = %p", fun, fun->left, fun->right);
	//execute
	Hash tmp = initHash(65536);
	*(fun->ptrlocalvars) = tmp;
	fun->ptrglobalvars = obj->vartable;
	debugmsg(EXECUTE,"creating local vars ... ... %p = %p ", fun->ptrlocalvars, tmp);
	if(node->left!=NULL){
		Data params = Ex(node->left);
		ExPARAMS(fun->left, params.value.arrayValue);
	}

	debugmsg(EXECUTE,"executing fun ... ..%p", fun);
	Data ret = Ex(fun);
	debugmsg(EXECUTE,"return ... ...%s", toString(&ret));
	debugmsg(EXECUTE,"freeing local vars ... ... ");
	freeHash(tmp);
	*(node->ptrlocalvars) = NULL;
	if(strcmp(funname.value.strValue,"new") == 0)
		return *(createPtrData(obj));
	return ret;
}


