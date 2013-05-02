/*
 * =====================================================================================
 *
 *       Filename:  funnode.c
 *
 *    Description:  e
 *
 *        Version:  1.0
 *        Created:  02/14/2013 09:29:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "funnode.h"
Node* createFUN(const char* name, Node* paramslist, Node* stmts){
	Node* ret = createEmptyNode();
	debugmsg(CREATE, "creating function ... ... %p param = %p stmts = %p ", ret, paramslist, stmts);
	debugmsg(CREATE,"assing op ..." );
	ret->op = FUN;
	debugmsg(CREATE, "assign ptrglobalvars ..." );
	ret->left = paramslist;
	debugmsg(CREATE,"assign stmts ..." );
	ret->right = stmts;
	debugmsg( CREATE,"done" );
	return ret;
}

Data ExFUN(Node* node, RuntimeEnv* env){
	debugmsg(EXECUTE, "executing FUN ... ... %p", node);
	Data ret = Ex(node->right);
	debugmsg(EXECUTE, "FUN  return ... ... %s", toString(&ret));
	return ret;
}

