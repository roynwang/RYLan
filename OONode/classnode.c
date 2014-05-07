/*
 * =====================================================================================
 *
 *       Filename:  classnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/09/2013 11:40:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "classnode.h"
#include "../debug.h"

ClassNode* createClassNode(ClassNode* parent ){
	ClassNode *ret = (ClassNode*)malloc(sizeof(ClassNode));
	ret->parent = parent;
	if(parent == NULL){
		//create a new class
		Hash tmpfun = initHash(HASHSIZE);
		Hash tmpvar = initHash(HASHSIZE);
		Hash* ptrtmpfun = (Hash*)malloc(sizeof(Hash*));
		Hash* ptrtmpvar = (Hash*)malloc(sizeof(Hash*));
		*ptrtmpfun = tmpfun;
		*ptrtmpvar = tmpvar;
		ret->vartable = ptrtmpvar;
		ret->funtable = ptrtmpfun;
	}
	else{
		//create a new class
		Hash tmpvar = dupHash(*(parent->vartable));
		ret->vartable = &tmpvar;
		ret->funtable = parent->funtable;
	}
	return ret;
}
void registerclass(const char* name ,Hash classtable, ClassNode *class){
	debugmsg(CREATE, "register class ... ...%s -> %p", name, class);
	setItem(classtable,name,class);
}
void registervar(const char* name, Data* value, ClassNode* class){
	debugmsg(CREATE, "register var ... ...%s -> %p", name, class);
	setItem( *(class->vartable), name,value);
}

void registerfun(const char* name, Node* fun, ClassNode* class){
	debugmsg(CREATE, "register fun ... ...%s -> %p", name, fun);
	setItem( *(class->funtable), name,fun);
}
Node* getfunmember(const char* name, ClassNode* class){
	Node* ret =  getItem(*(class->funtable), name);
	debugmsg(EXECUTE, "query function ... ... %s -> %p", name, ret);
	return ret;
}

