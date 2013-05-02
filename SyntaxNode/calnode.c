/*
 * =====================================================================================
 *
 *       Filename:  calnode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:00:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "calnode.h"

Data ExADD(Node* node){
	debugmsg(EXECUTE, "ADD ... ... %p", node);
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return adddata(*(node->ptrglobalvars), &l, &r);
}
Data ExSUB(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return subdata(*(node->ptrglobalvars),&l,&r);
}
Data ExMUL(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return muldata(*(node->ptrglobalvars),&l,&r);
}
Data ExDIV(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return divdata(*(node->ptrglobalvars),&l,&r);
}
Data ExCompare(int comp, Node* node){
	if(comp == ST){
		debugmsg(EXECUTE, "executing ST ... ...");
		Data l = Ex(node->left);
		Data r = Ex(node->right);
		Data ret = comparedata(*(node->ptrglobalvars),&l,&r);
		return  ret.value.intValue<0?TRUE : FALSE;
	}
}
Node* createComplex(int op, Node* left, Node* right){
	Node* ret = createEmptyNode();
	debugmsg(CREATE, "creating expr ... ... %p (%s %p %p)",ret, optoStr(op), left,right);
	ret->op =  op;
	ret->left = left;
	ret->right = right;
	return ret;
}


