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
#include "utility.h"

int ex(Node* node){
	if(node->op == AssignOP){
		VarList[*(node->symbol)] =  ex(node->next);
		return VarList[*(node->symbol)];
	}
	if(node->next != NULL)
		ex(node->next);
}

