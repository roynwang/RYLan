/*
 * =====================================================================================
 *
 *       Filename:  logicnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 10:00:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "logicnode.h"
Node* createNOT(Node* expr){
	Node* ret = createEmptyNode();
	ret->op =  NOT;
	ret->left = expr;
	return ret;
}

