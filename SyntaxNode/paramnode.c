/*
 * =====================================================================================
 *
 *       Filename:  paramnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:11:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "paramnode.h"
Data ExPARAMS(Node* node, ArrayUnit* actualParams){
	//actual params should be array
	Data *dup = createEmptyData();
	Data * av = getValue(*(node->ptrglobalvars),actualParams->data);
	memcpy(dup, av, sizeof(Data));
	setItem(*(node->ptrglobalvars),node->data->value.strValue,dup);
	actualParams = actualParams->next;
	if(node->right != NULL){
		ExPARAMS(node->right, actualParams);
	}
	return TRUE;
}
Node* createPARAM(char* name){
	Node* ret = createEmptyNode();
	debugmsg (CREATE, "creating param ... ... %p %s", ret, name );
	ret->op =  PARAMS;
	ret->data = createStrData(name);
	return ret;
}

Node* createPARAMS(Node* param, Node* params){
	param->right = params;
	return param;
}


