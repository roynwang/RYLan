/*
 * =====================================================================================
 *
 *       Filename:  displaynode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 08:10:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  DISPLAYNODE_INC
#define  DISPLAYNODE_INC
#include "node.h"
#include "../GlobalHashTable/dataunit.h"



Node* createDISPLAY(Node* value);

Data ExDISPLAY(Node* node, RuntimeEnv env);
#endif   /* ----- #ifndef DISPLAYNODE_INC  ----- */
