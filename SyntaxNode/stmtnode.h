/*
 * =====================================================================================
 *
 *       Filename:  stmtnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 08:34:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  STMTNODE_INC
#define  STMTNODE_INC

#include "node.h"

Node* createSTMT(Node* stmt, Node* stmts);
Data ExSTMT(Node* node, RuntimeEnv* env);

#endif   /* ----- #ifndef STMTNODE_INC  ----- */
