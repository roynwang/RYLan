/*
 * =====================================================================================
 *
 *       Filename:  objectnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/08/2013 09:42:21 PM
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
#include "objectnode.h"


ObjectNode* createEmptyObjectNode(){
	ObjectNode* ret = (ObjectNode*)malloc(sizeof(ObjectNode));
	ret->vartable = NULL;
	ret->type = NULL;
	return ret;
}

ObjectNode* createObject(char* classname, Hash classtable){
	ClassNode* type = getItem(classtable,  classname);
	ObjectNode* ret = createEmptyObjectNode();
	ret->type = type;
	Hash* ptrhash = (Hash*)malloc(sizeof(Hash*));
	*ptrhash = dupHash(*(type->vartable));
	ret->vartable = ptrhash;
	return ret;
}






