/*
 * =====================================================================================
 *
 *       Filename:  assignnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 08:42:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  ASSIGNNODE_INC
#define  ASSIGNNODE_INC

#include "node.h"
Node* createASSIGN(Node* left, Node* right);
Data ExASSIGN(Node* node, RuntimeEnv* env);
#endif   /* ----- #ifndef ASSIGNNODE_INC  ----- */
