/*
 * =====================================================================================
 *
 *       Filename:  paramnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:11:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  PARAMNODE_INC
#define  PARAMNODE_INC
#include "node.h"
#include "memory.h"
Node* createPARAM(char* name);

Node* createPARAMS(Node* param, Node* params);

Data ExPARAMS(Node* node, ArrayUnit* actualParams);
#endif   /* ----- #ifndef PARAMNODE_INC  ----- */
