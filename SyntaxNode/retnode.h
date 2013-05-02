/*
 * =====================================================================================
 *
 *       Filename:  retnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:18:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  RETNODE_INC
#define  RETNODE_INC

#include "node.h"
#include "memory.h"

Node* createRET(Node* value);
Data ExRET(Node* node);


#endif   /* ----- #ifndef RETNODE_INC  ----- */
