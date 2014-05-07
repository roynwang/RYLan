/*
 * =====================================================================================
 *
 *       Filename:  simplenode.c
 *
 *    Description:  create simple data node
 *
 *        Version:  1.0
 *        Created:  02/14/2013 08:02:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "simplenode.h"
Node* createVar(char* name){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createVarData(name);
	
	debugmsg(CREATE,"%p create var ... ... %s", ret,name);
	return ret;
}
Node* createStr(const char* value){
	Node* ret = createEmptyNode();;
	ret->op =  GET;
	ret->data = createStrData(value);
	debugmsg(CREATE,"%p create str ... ... %s", ret, value);
	return ret;
}
Node* createInt(int value){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createIntData(value);
	debugmsg(CREATE,"%p create int ... ... %d",ret, value);
	return ret;
}
Node* createArray(ArrayUnit *arr){
	debugmsg(CREATE,"create arr ... ... %p",arr);
	if(arr == NULL) return NULL;
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createArrayData(arr);
	return ret;
}
Node* createPtr(void* value){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createPtrData(value);
	return ret;
}

Data ExGET(Node* node){
	debugmsg(EXECUTE, "GET ... ... %p %s", node, toString(node->data));
	return *(node->data);
}
