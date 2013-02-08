/*
 * =====================================================================================
 *
 *       Filename:  classnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/08/2013 09:14:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  CLASSNODE_INC
#define  CLASSNODE_INC
#include "../GlobalHashTable/hash.h"

typedef struct _ClassNode{
	Hash* funtable;
	Hash* vartable;
	struct _ClassNode* parent;
}ClassNode;

#endif   /* ----- #ifndef CLASSNODE_INC  ----- */
