/*
 * =====================================================================================
 *
 *       Filename:  objvarnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:22:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "objvarnode.h"
#include "simplenode.h"
#include "../OONode/objectnode.h"
Node* createOBJVAR(char* objname, char* varname){
	Node* ret = createEmptyNode();
	debugmsg(CREATE,"creating OBJVAR ... ...%p", ret);
	ret->op = OBJVAR;
	ret->left = createStr(objname);
	ret->right = createStr(varname);
	return ret;
}

Data ExOBJVAR(Node* node){
	debugmsg(EXECUTE, "executing OBJVAR ... ... %p", node);
	Data objname = Ex(node->left);
	Data varname = Ex(node->right);
	debugmsg(EXECUTE, "queried obj:%s var:%s ... ... ", objname.value.strValue, varname.value.strValue);
	Data* ptrobj = getbyName(objname.value.strValue,*(node->ptrglobalvars), *(node->ptrlocalvars));
	debugmsg(EXECUTE, "queried obj ... ... %p", ptrobj);
	ObjectNode* obj = (ObjectNode*)ptrobj->value.ptrValue;
	Data* ptrret = getbyName(varname.value.strValue,*(obj->vartable),NULL);
	Data ret = *ptrret;
	return ret;
}


