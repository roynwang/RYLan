/*
 * =====================================================================================
 *
 *       Filename:  displaynode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 10:24:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "displaynode.h"
Data ExDISPLAY(Node* node, RuntimeEnv env){
	debugmsg(EXECUTE, "DISPLAY ... ... %p", node);
	Data var = Ex(node->right);
	Data* intv = getItem(*(node->ptrglobalvars), var.value.varValue);
	printf("!!!REUSLT = %d\n", intv->value.intValue); 
	return EMPTY;
}
Node* createDISPLAY(Node* value){
	Node* ret = createEmptyNode();
	ret->op =  DISPLAY;
	ret->right = value;
	return ret;
}
