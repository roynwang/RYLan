/*
 * =====================================================================================
 *
 *       Filename:  garbage.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/09/2013 08:07:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  GARBAGE_INC
#define  GARBAGE_INC

#include "../SyntaxNode/node.h"
#include "../GlobalHashTable/dataunit.h"



typedef enum {
	DATATYPE, NODETYPE, HASHTYPE
}ResType;

typedef struct _datares{
	union {
		Data* datares;
		Node* noderes;
		Hash hashres;
	} data;
	struct _datares* next;
}DataRes;

typedef struct _resource{
	DataRes*  res;
}Resource;

Resource *datares ;
Resource *noderes ;
Resource *hashres ;

void addres(char restype, void *res);
void initialGC();
void finializeMem();
#endif   /* ----- #ifndef GARBAGE_INC  ----- */
