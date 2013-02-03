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
	ret->ismarkedforfree = 0;
	ret->op = NONE;
	ret->left = NULL;
	ret->right = NULL;
	ret->ptrlocalvars = NULL;
	ret->ptrfuncs = NULL;
	ret->data = NULL;
	return ret;
}

Data ExGET(Node* node){
	printf ( "Executing GET ... ...\n" );
	return *(node->data);
}
Data ExDISPLAY(Node* node){
	printf("Execute DISPLAY ... ...\n");
	Data var = Ex(node->right);
	printf ( ".............. %s\n", var.value.varValue);
	Data* intv = getItem(*(node->ptrlocalvars), var.value.varValue);
	printf("!!!REUSLT = %d\n", intv->value.intValue); 
}
Data ExASSIGN(Node* node){
	printf ( "Executing ASSIGN ... ...\n" );
	const char* name = Ex(node->left).value.varValue;
	Data src = Ex(node->right);
	Data* dest = createEmptyData();
	memcpy(dest, &src, sizeof(src));
	printf ( "ASSIGN: Name = %s value = %d\n", name, dest->value.intValue );
	setItem(*(node->ptrlocalvars), name, (void*)dest);
	return TRUE;
}
Data ExADD(Node* node){
	printf ( "Executing ADD ... ...\n" );
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return adddata(*(node->ptrlocalvars), &l, &r);
}
Data ExSUB(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return subdata(*(node->ptrlocalvars),&l,&r);
}
Data ExMUL(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return muldata(*(node->ptrlocalvars),&l,&r);
}
Data ExDIV(Node* node){
	Data l = Ex(node->left);
	Data r = Ex(node->right);
	return divdata(*(node->ptrlocalvars),&l,&r);
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
		Data ret = comparedata(*(node->ptrlocalvars),&l,&r);
		return  ret.value.intValue<0?TRUE : FALSE;
	}
}
Data ExPARAMS(Node* node, ArrayUnit* actualParams){
	//actual params should be array
	Data *dup = createEmptyData();
	Data * av = getValue(*(node->ptrlocalvars),actualParams->data);
	memcpy(dup, av, sizeof(Data));
	setItem(*(node->ptrlocalvars),node->data->value.strValue,dup);
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
	//create new local vars
	printf ( "Executing FUNCALL\n" );
	if(node->left!=NULL){
		Data params = ExGET(node->left);
		printf("param array : %p\n", params.value.arrayValue);

		ExPARAMS(node->right->left, params.value.arrayValue);
	}
	return Ex(node->right);
}
Data ExFUN(Node* node){
	return Ex(node->right);
}
void freeNode(Node* node){
	if(node!=NULL && node->ismarkedforfree == 0){
		node->ismarkedforfree = 1;
		printf ( "free NODE: %p\n", node);
		freeNode(node->left);
		freeNode(node->right);
		if(node->ptrlocalvars!=NULL){
			printf ( "!!!!&hash %p !!!!!!!!!!!\n",  node->ptrlocalvars);
			if(*(node->ptrlocalvars) != NULL)
			{

				printf ( "!!!!!!!!hash %p !!!!!!!!!!\n",  *(node->ptrlocalvars));
				freeHash(*(node->ptrlocalvars));
			}
			*(node->ptrlocalvars) = NULL;
			printf ( "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" );
		}
		if(node->data!=NULL){
			freeData(node->data);
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
Node* createPtr(void* value){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createPtrData(value);
	return ret;
}
Node* createDISPLAY(Node* value, Hash* ptrlocalvars){
	Node* ret = createEmptyNode();
	ret->op =  DISPLAY;
	ret->ptrlocalvars = ptrlocalvars;
	ret->right = value;
	return ret;
}

Node* createNOT(Node* expr, Hash * ptrlocalvars){
	Node* ret = createEmptyNode();
	ret->op =  NOT;
	ret->left = expr;
	ret->ptrlocalvars = ptrlocalvars;
	return ret;
}
Node* createIF(Node* expr, Node* thenstmt, Hash *ptrlocalvars){
	Node* ret = createEmptyNode();
	ret->op =  IF;
	ret->left = expr;
	ret->right = thenstmt;
	ret->ptrlocalvars = ptrlocalvars;
	return ret;
}

Node* createIFELSE(Node* expr, Node* thenstmt, Node* elsestmt, Hash *ptrlocalvars){
	Node* ret = createEmptyNode();
	ret->op =  IF;
	ret->left = createNOT(createIF(expr, thenstmt,ptrlocalvars), ptrlocalvars);
	ret->right = elsestmt;
	ret->ptrlocalvars = ptrlocalvars;
	return ret;
}
Node* createComplex(int op, Node* left, Node* right, Hash* ptrlocalvars){

	printf ( "creating expr: %d \n",op );
	Node* ret = createEmptyNode();
	ret->op =  op;
	ret->left = left;
	ret->right = right;
	ret->ptrlocalvars = ptrlocalvars;
	return ret;
}

Node* createPARAM(char* name, Hash* ptrlocalvars){
	Node* ret = createEmptyNode();
	ret->op =  PARAMS;
	ret->ptrlocalvars = ptrlocalvars;
	ret->data = createStrData(name);
	printf ( "creating param: %p %s\n", ret, name );
	return ret;
}

Node* createPARAMS(Node* param, Node* params){
	param->right = params;
	return param;
}

Node* createSTMTS(Node* stmt, Node* stmts, Hash *ptrlocalvars){
	Node* ret = createEmptyNode();
	ret->op =  STMT;
	ret->left = stmt;
	ret->right = stmts;
	ret->ptrlocalvars = ptrlocalvars;
	printf("create STMTS %p\n", ret);
	return ret;
}

Node* createWHILE(Node* judge, Node* body, Hash *ptrlocalvars){
	Node* stmts = createSTMTS(body, NULL,ptrlocalvars);
	Node* ret= createIF(judge, stmts, ptrlocalvars);
	ret->ptrlocalvars = ptrlocalvars;
	stmts->right = ret;
	return ret;
}

Node* createFOR(Node* initial, Node* judge, Node* step, Node* body, Hash *ptrlocalvars){
	Node* whilestmt = createWHILE(judge, createSTMTS(body,step,ptrlocalvars),ptrlocalvars);
	return createSTMTS(initial, whilestmt,ptrlocalvars);
}

Node* createFUN(char* name, Node* paramslist, Node* stmts, Hash *ptrlocalvars, Hash *ptrfunhash){
	printf ( "param = %p stmts = %p varstable = %p\n",paramslist, stmts, ptrlocalvars );
	printf("creating FUN \n");
	Node* ret = createEmptyNode();
	printf ( "assing op ... " );
	ret->op = FUN;
	printf ( "done\n assign ptrlocalvars ..." );
	ret->ptrlocalvars = ptrlocalvars;
	printf ( "done\n assign param %p... ", paramslist );
	ret->left = paramslist;
	printf ( "done\n assign stmts ..." );
	ret->right = stmts;
	printf ( "done\n" );
	ret->ptrfuncs = ptrfunhash;
	//register the function
	printf ( "register funcation '%s'\n", name );
	Data* ptrfun = createPtrData(ret);
	setItem(*ptrfunhash, name, ptrfun); 
	return ret;
}
Node* createFUNCALL(Hash *funHash, char* name, Node* paramslist, Hash* ptrlocalvars){
	Node* ret = createEmptyNode();
	ret->op = FUNCALL;
	ret->left = paramslist;
//	ret->left = createArray(paramslist);

	Data* ptrfun = getItem(*funHash, name);
	Node* fun = (Node*)ptrfun->value.ptrValue;
	
	ret->right = fun;
	ret->ptrlocalvars = ptrlocalvars;
	ret->ptrfuncs = funHash;
	return ret;
}

Data Ex(Node* node){
	if(node == NULL) return EMPTY;
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
		case FUN:
		return ExFUN(node);
		case DISPLAY:
			return ExDISPLAY(node);
		default:
			break;   
	}
}

