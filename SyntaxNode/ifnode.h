/*
 * =====================================================================================
 *
 *       Filename:  ifnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 09:43:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  IFNODE_INC
#define  IFNODE_INC
#include "node.h"

Node* createIF(Node* expr, Node* thenstmt);
Data ExIF(Node* node);
Node* createIFELSE(Node* expr, Node* thenstmt, Node* elsestmt);
#endif   /* ----- #ifndef IFNODE_INC  ----- */
