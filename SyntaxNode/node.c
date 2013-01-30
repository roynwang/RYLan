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
#include <stdio.h>


Node * createEmptyNode(){
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->op = NONE;
	ret->left = NULL;
	ret->right = NULL;
	ret->localvars = NULL;
	ret->data = NULL;
	return ret;
}

Data ExGET(Node* node){
	printf ( "Executing GET ... ...\n" );
	return *(node->data);
}
Data ExASSIGN(Node* node){
	printf ( "Executing ASSIGN ... ...\n" );
	const char* name = Ex(node->left).value.varValue;
	Data src = Ex(node->right);
	Data* dest = (Data*)malloc(sizeof(Data));
	memcpy(dest, &src, sizeof(src));
	printf ( "ASSIGN: Name = %s value = %d\n", name, dest->value.intValue );
	setItem(node->localvars, name, (void*)dest);
	return TRUE;
}
Data ExADD(Node* node){
	printf ( "Executing ADD ... ...\n" );
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return adddata(node->localvars, &l, &r);
}
Data ExSUB(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return subdata(node->localvars,&l,&r);
}
Data ExMUL(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return muldata(node->localvars,&l,&r);
}
Data ExDIV(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return divdata(node->localvars,&l,&r);
}
Data ExIF(Node* node){
	Data l = Ex(node->left);
	if(isTrue(&l)){
		Ex(node->right);
		return TRUE;
	}
	return FALSE;
}
Data ExCompare(int comp, Node* node){
	if(comp == ST){
		Data l = Ex(node->left);
		Data r = Ex(node->right);
		Data ret = comparedata(node->localvars,&l,&r);
		return  ret.value.intValue<0?TRUE : FALSE;
	}
}
Data ExPARAMS(Node* node, ArrayUnit* actualParams){
	//actual params should be array
	Data *dup = (Data*)malloc(sizeof(Data));
	memcpy(dup, actualParams->data, sizeof(Data));
	setItem(node->localvars,node->data->value.strValue,dup);
	actualParams = actualParams->next;
	if(node->right != NULL){
		ExPARAMS(node->right, actualParams);
	}
}
Data ExSTMT(Node* node){
	Ex(node->left);
	Ex(node->right);
}
Data ExFUNCALL(Node* node){
	//set param
	Data params = ExGET(node->left);
	ExPARAMS(node->right->left, params.value.arrayValue);
	return ExSTMT(node->right);
}
Data ExFUN(Node* node){
	return ExSTMT(node->right);
}
void freeNode(Node* node){
	if(node!=NULL){
		freeNode(node->left);
		freeNode(node->right);
//		printf ( "free localvars %p ... \n",node->localvars );
//		if(node->localvars!=NULL)
//			freeHash(node->localvars);
//		printf ( "done",node->localvars );
		if(node->data!=NULL){
			free(node->data);
		}
		free(node);
	}
}

Node* createVar(char* name){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createVarData(name);
	return ret;
}
Node* createStr(char* value){
	Node* ret = createEmptyNode();;
	ret->op =  GET;
	ret->data = createStrData(value);
	return ret;
}
Node* createInt(int value){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createIntData(value);
	return ret;
}
Node* createArray(ArrayUnit *arr){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createArrayData(arr);
	return ret;
}
Node* createNOT(Node* expr, Hash localvars){
	Node* ret = createEmptyNode();
	ret->op =  NOT;
	ret->left = expr;
	ret->localvars = localvars;
	return ret;
}
Node* createIF(Node* expr, Node* thenstmt, Hash localvars){
	Node* ret = createEmptyNode();
	ret->op =  IF;
	ret->left = expr;
	ret->right = thenstmt;
	ret->localvars = localvars;
	return ret;
}

Node* createIFELSE(Node* expr, Node* thenstmt, Node* elsestmt, Hash localvars){
	Node* ret = createEmptyNode();
	ret->op =  IF;
	ret->left = createNOT(createIF(expr, thenstmt,localvars), localvars);
	ret->right = elsestmt;
	ret->localvars = localvars;
	return ret;
}
Node* createComplex(int op, Node* left, Node* right, Hash localvars){
	Node* ret = createEmptyNode();
	ret->op =  op;
	ret->left = left;
	ret->right = right;
	ret->localvars = localvars;
	return ret;
}

Node* createPARAM(char* name, Hash localvars){
	Node* ret = createEmptyNode();
	ret->op =  PARAMS;
	ret->localvars = localvars;
	ret->data = createStrData(name);
	return ret;
}

Node* createPARAMS(Node* param, Node* params){
	param->right = params;
	return param;
}

Node* createSTMTS(Node* stmt, Node* stmts, Hash localvars){
	Node* ret = createEmptyNode();
	ret->op =  STMT;
	ret->left = stmt;
	ret->right = stmts;
	ret->localvars = localvars;
	return ret;
}

Node* createWHILE(Node* judge, Node* body, Hash localvars){
	Node* stmts = createSTMTS(body, NULL,localvars);
	Node* ret= createIF(judge, stmts, localvars);
	ret->localvars = localvars;
	stmts->right = ret;
	return ret;
}

Node* createFOR(Node* initial, Node* judge, Node* step, Node* body, Hash localvars){
	Node* whilestmt = createWHILE(judge, createSTMTS(body,step,localvars),localvars);
	return createSTMTS(initial, whilestmt,localvars);
}

Node* createFUN(Node* paramslist, Node* stmts, Hash localvars){
	Node* ret = createEmptyNode();
	ret->op = FUN;
	ret->localvars = localvars;
	ret->left = paramslist;
	ret->right = stmts;
	return ret;
}
Node* createFUNCALL(Hash funHash, char* name, ArrayUnit* paramslist, Hash localvars){
	Node* ret = createEmptyNode();
	ret->op = FUNCALL;
	ret->left = createArray(paramslist);
	Node* fun = (Node*)getItem(funHash, name);
	ret->right = fun;
	ret->localvars = localvars;
	return ret;
}

Data Ex(Node* node){
	switch(node->op){
		case GET:
			return ExGET(node);
		case ASSIGN:
			return ExASSIGN(node);
		case ADD:
			return ExADD(node);
		case SUB:
			return ExSUB(node);
		case MUL:
			return ExMUL(node);
		case DIV:
			return ExDIV(node);
		case IF:
			return ExIF(node);
		case ST:
			return ExCompare(ST,node);
		case FUNCALL:
			return ExFUNCALL(node);
		case STMT:
			return ExSTMT(node);
		default:
			break;   
	}
}

