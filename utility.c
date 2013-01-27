/*
 * =====================================================================================
 *
 *       Filename:  utility.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/26/2013 01:58:35 AM
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
#include "utility.h"

int DEBUG = 3;
int ex(Node* node){
	printf("[3] Calculating ");
	if(node->op == AssignOp){
		printf("ASSIGN ");
		printf("SYMBOL::%s value:: %d\n",node->varName, node->intValue);
		return 0xFFFF;
	}
	if(node->op == AddOp){
		return node->intValue + ex(node);
	}
	if(node->next != NULL)
		ex(node->next);
}

