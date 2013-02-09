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
#include "../GlobalHashTable/dataunit.h"
#include "../SyntaxNode/node.h"


typedef struct _ClassNode{
	Hash* funtable;
	Hash* vartable;
	struct _ClassNode* parent;
}ClassNode;

ClassNode* createClassNode(ClassNode* parent);

void registerclass(const char* name ,Hash classtable, ClassNode *class);
void registervar(const char* name, Data* value, ClassNode* class);
void registerfun(const char* name, Node* fun, ClassNode* class);
#endif   /* ----- #ifndef CLASSNODE_INC  ----- */
