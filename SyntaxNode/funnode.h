/*
 * =====================================================================================
 *
 *       Filename:  funnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 08:36:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  FUNNODE_INC
#define  FUNNODE_INC

#include "node.h"

Node* createFUN(const char* name, Node* params, Node* stmts);
Data ExFUN(Node* node, RuntimeEnv* env);

#endif   /* ----- #ifndef FUNNODE_INC  ----- */

