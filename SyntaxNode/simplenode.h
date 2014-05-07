/*
 * =====================================================================================
 *
 *       Filename:  simplenode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 08:01:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  SIMPLENODE_INC
#define  SIMPLENODE_INC

#include "node.h"
#include "../GlobalHashTable/dataunit.h"
Node* createVar(char* name);
Node* createStr(const char* value);
Node* createInt(int value);
Node* createArray(ArrayUnit *arr);
Node* createPtr(void* value);


#endif   /* ----- #ifndef SIMPLENODE_INC  ----- */
