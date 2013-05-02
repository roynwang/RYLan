/*
 * =====================================================================================
 *
 *       Filename:  node.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/28/2013 09:45:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <memory.h>
#include "node.h"
#include "../debug.h"
#include "../GC/gc.h"
#include "../OONode/classnode.h"
#include "../OONode/objectnode.h"
#include <stdio.h>
#include "syntaxnode.h"


Hash* curptrvarshash = NULL;
Hash* ptrclasstable = NULL;

char* optoStr(int op){
	switch(op){
		case ST:
			return "ST";
		case ADD:
			return "ADD";
		default:
			return "DEFAULT";
	}
}

Hash* getcurhash(){
	if(curptrvarshash == NULL){
		curptrvarshash = (Hash*)malloc(sizeof(Hash*));
		*curptrvarshash = NULL;
	}
	return curptrvarshash;
}

void resetcurhash(){
	curptrvarshash = NULL;
}

Data* getbyName(char* name, Hash globalhash, Hash localhash){
	debugmsg(EXECUTE,"local = %p global = %p", localhash, globalhash);
	Data* ret= getItem(localhash,name);
	debugmsg(EXECUTE,"GET from local ... ... %p",ret);
	if(ret == NULL){
		ret = getItem(globalhash,name);
		debugmsg(EXECUTE,"GET from global ... ... %p",ret);
	}
	return ret;
}

void setbyName(char* name, Data* value,Hash globalhash, Hash localhash){
	Data* gitem = getItem(globalhash, name);
	Data* litem = getItem(localhash, name);
	if(litem == NULL && gitem!=NULL)
		setItem(globalhash,name,value);
	else
		setItem(localhash,name,value);
}

Node * createEmptyNode(){
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->ismarkedforfree = 0;
	ret->op = NONE;
	ret->left = NULL;
	ret->right = NULL;
	ret->env = NULL;
	ret->data = NULL;
	addres(NODETYPE, ret);
	return ret;
}
void freeNode(Node* node){
    debugmsg(FREE, "free node ... ... %p", node);
	free(node);
}

Data Ex(Node* node){
	if(node == NULL) return EMPTY;
	debugmsg(EXECUTE, "Executing %p left:%p right:%p", node, node->left, node->right);
	return EMPTY;
}

void setClassHash(Hash* classhash){
	ptrclasstable = classhash;
}


