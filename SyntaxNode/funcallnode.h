/*
 * =====================================================================================
 *
 *       Filename:  funcallnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 09:08:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  FUNCALLNODE_INC
#define  FUNCALLNODE_INC
#include "node.h"
//should create env here

Node* createFUNCALL(const char* objname, const char* funname, Node* paramslist);
Node* ExFUNCALL(Node* node);
#endif   /* ----- #ifndef FUNCALLNODE_INC  ----- */
