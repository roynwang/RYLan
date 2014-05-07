/*
 * =====================================================================================
 *
 *       Filename:  loopnode.h
 *
 *    Description:  e
 *
 *        Version:  1.0
 *        Created:  02/14/2013 08:13:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  LOOPNODE_INC
#define  LOOPNODE_INC
#include "node.h"

Node* createWHILE(Node* judge, Node* body);
Node* createFOR(Node* initial, Node* judge, Node* step, Node* body);

#endif   /* ----- #ifndef LOOPNODE_INC  ----- */
