/*
 * =====================================================================================
 *
 *       Filename:  assignnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:40:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <memory.h>

#include "assignnode.h"
Data ExASSIGN(Node* node, RuntimeEnv* env){
	const char* name = Ex(node->left).value.varValue;
	Data src = Ex(node->right);
	Data* dest = createEmptyData();
	memcpy(dest, &src, sizeof(src));
	debugmsg (EXECUTE, "ASSIGN: Name = %s value = %d", name, dest->value.intValue );
	setItem(*(node->ptrglobalvars), name, (void*)dest);
	debugmsg (EXECUTE,"ASSIGN DONE");
	return TRUE;
}

