/*
 * =====================================================================================
 *
 *       Filename:  calnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:00:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  CALNODE_INC
#define  CALNODE_INC
#include "node.h"
Data ExADD(Node* node);
Data ExSUB(Node* node);
Data ExMUL(Node* node);
Data ExDIV(Node* node);
Data ExCompare(int comp,Node* node);
Node* createComplex(int op, Node* left, Node* right);
#endif   /* ----- #ifndef CALNODE_INC  ----- */
