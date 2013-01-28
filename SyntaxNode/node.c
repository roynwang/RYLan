/*
 * =====================================================================================
 *
 *       Filename:  node.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/28/2013 09:45:19 PM
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
#include "node.h"
Data Ex(Node* node){
	if(node->op = GET){
		        return *(node->data);
	}
	if(node->op == ASSIGN){
		char* name = Ex(node->left).value.varValue;
		Data src = Ex(node->right);
		Data* dest = (Data*)malloc(sizeof(Data));
		memcpy(dest, &src, sizeof(src));
		setItem(node->localvars, name, dest);
		return *dest;
	}
	if(node->op == ADD){
		Data l = Ex(node->left);
		Data r = Ex(node->right);
		return adddata(node->localvars, &l, &r);
	}
	if(node->op == SUB){
		Data l = Ex(node->left);
		Data r = Ex(node->right);
		return subdata(node->localvars,&l,&r);
	}
	if(node->op == MUL){
		Data l = Ex(node->left);
		Data r = Ex(node->right);
		return muldata(node->localvars,&l,&r);
	}
	if(node->op == DIV){
		Data l = Ex(node->left);
		Data r = Ex(node->right);
		return divdata(node->localvars,&l,&r);
	}
}
