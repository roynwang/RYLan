/*
 * =====================================================================================
 *
 *       Filename:  objectnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        02/08/2013 09:21:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  OBJECTNODE_INC
#define  OBJECTNODE_INC

#include "../GlobalHashTable/hash.h"
#include "classnode.h"

typedef struct _ObjectNode{
	Hash* vartable;
	ClassNode* type;
} ObjectNode;

ObjectNode* createObject(char* classname, Hash classtable);
	
#endif   /* ----- #ifndef OBJECTNODE_INC  ----- */
