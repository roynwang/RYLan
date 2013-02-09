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
#include "../debug.h"
#include "../GC/gc.h"
#include <stdio.h>


Hash* curptrvarshash = NULL;

char* optoStr(int op){
	switch(op){
		case ST:
			return "ST";
		case ADD:
			return "ADD";
		default:
			return "DEFAULT";
	}
}

Hash* getcurhash(){
	if(curptrvarshash == NULL){
		curptrvarshash = (Hash*)malloc(sizeof(Hash*));
		*curptrvarshash = NULL;
	}
	return curptrvarshash;
}

void resetcurhash(){
	curptrvarshash = NULL;
}

Data* getbyName(char* name, Hash globalhash, Hash localhash){
	Data* ret= getItem(localhash,name);
	if(ret == NULL)
		ret= getItem(globalhash,name);
	return ret;
}

void setbyName(char* name, Data* value,Hash globalhash, Hash localhash){
	Data* gitem = getItem(globalhash, name);
	Data* litem = getItem(localhash, name);
	if(litem == NULL && gitem!=NULL)
		setItem(globalhash,name,value);
	else
		setItem(globalhash,name,value);
}


Node * createEmptyNode(){
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->ismarkedforfree = 0;
	ret->op = NONE;
	ret->left = NULL;
	ret->right = NULL;
	ret->ptrglobalvars = NULL;
	ret->ptrlocalvars = getcurhash();
	ret->ptrfuncs = NULL;
	ret->data = NULL;
	addres(NODETYPE, ret);
	return ret;
}

Data ExGET(Node* node){
	debugmsg(EXECUTE, "GET ... ... %p %s", node, toString(node->data));
	return *(node->data);
}
Data ExDISPLAY(Node* node){
	debugmsg(EXECUTE, "DISPLAY ... ... %p", node);
	Data var = Ex(node->right);
	Data* intv = getItem(*(node->ptrglobalvars), var.value.varValue);
	printf("!!!REUSLT = %d\n", intv->value.intValue); 
	return EMPTY;
}
Data ExASSIGN(Node* node){
	const char* name = Ex(node->left).value.varValue;
	Data src = Ex(node->right);
	Data* dest = createEmptyData();
	memcpy(dest, &src, sizeof(src));
	debugmsg (EXECUTE, "ASSIGN: Name = %s value = %d", name, dest->value.intValue );
	setItem(*(node->ptrglobalvars), name, (void*)dest);
	return TRUE;
}
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
Data ExIF(Node* node){
	Data l = Ex(node->left);
	debugmsg (EXECUTE, "executing if ... ..." );
	if(isTrue(&l)){
		debugmsg (EXECUTE, "TRUE ... ..." );
		Ex(node->right);
		return TRUE;
	}
	return FALSE;
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
Data ExPARAMS(Node* node, ArrayUnit* actualParams){
	//actual params should be array
	Data *dup = createEmptyData();
	Data * av = getValue(*(node->ptrglobalvars),actualParams->data);
	memcpy(dup, av, sizeof(Data));
	setItem(*(node->ptrglobalvars),node->data->value.strValue,dup);
	actualParams = actualParams->next;
	if(node->right != NULL){
		ExPARAMS(node->right, actualParams);
	}
	return TRUE;
}
Data ExSTMT(Node* node){
	Data left = Ex(node->left);
	Data right = Ex(node->right);
	return right.valueType == EMPTY.valueType  ? left : right;
}
Data ExFUNCALL(Node* node){
	//set param
	//create new local vars
	debugmsg(EXECUTE,"executing FUN ... ... %p", node);

//	Hash tmp = initHash(65536);
//	*(node->ptrlocalvars) = tmp;
//
//	debugmsg(EXECUTE,"creating local vars ... ... %p = %p ", node->ptrlocalvars, tmp);

	//query fun
	Data* ptrfun = getItem(*(node->ptrfuncs), node->right->data->value.strValue);

	Node* fun = (Node*)ptrfun->value.ptrValue;

	debugmsg(EXECUTE,"queried fun ... ..%p", fun);
	Hash tmp = initHash(65536);
	*(fun->ptrlocalvars) = tmp;
	debugmsg(EXECUTE,"creating local vars ... ... %p = %p ", fun->ptrlocalvars, tmp);


	//done


	if(node->left!=NULL){
		Data params = ExGET(node->left);
		ExPARAMS(fun->left, params.value.arrayValue);
	}

	debugmsg(EXECUTE,"executing fun ... ..%p", fun);
	Data ret = Ex(fun);
	debugmsg(EXECUTE,"return ... ...%s", toString(&ret));
	debugmsg(EXECUTE,"freeing local vars ... ... ");
	freeHash(tmp);
	*(node->ptrlocalvars) = NULL;
	return ret;
}
Data ExFUN(Node* node){
	debugmsg(EXECUTE, "executing FUN ... ... %p", node);
	Data ret = Ex(node->right);
	debugmsg(EXECUTE, "FUN  return ... ... %s", toString(&ret));
	return ret;
}
Data ExRET(Node* node){
	debugmsg(EXECUTE, "executing RET ... ... %p", node);
	Data ret = Ex(node->left);
	if(ret.valueType == VarType){
		Data* tmp = getbyName(ret.value.varValue, *(node->ptrglobalvars), *(node->ptrlocalvars));
		memcpy(&ret, tmp, sizeof(Data));
	}
	debugmsg(EXECUTE, "return ... ... %s", toString(&ret));
	return ret;
}
void freeNode(Node* node){
    debugmsg(FREE, "free node ... ... %p", node);
	if(node->op == FUN){
		free(node->ptrlocalvars);
	}
	free(node);
}

Node* createVar(char* name){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createVarData(name);
	
	debugmsg(CREATE,"%p create var ... ... %s", ret,name);
	return ret;
}
Node* createStr(char* value){
	Node* ret = createEmptyNode();;
	ret->op =  GET;
	ret->data = createStrData(value);
	debugmsg(CREATE,"%p create str ... ... %s", ret, value);
	return ret;
}
Node* createInt(int value){
	Node* ret = createEmptyNode();
	ret->op =  GET;
	ret->data = createIntData(value);
	debugmsg(CREATE,"%p create int ... ... %d",ret, value);
	return ret;
}
Node* createArray(ArrayUnit *arr){
	debugmsg(CREATE,"create arr ... ... %p",arr);
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
Node* createDISPLAY(Node* value, Hash* ptrglobalvars){
	Node* ret = createEmptyNode();
	ret->op =  DISPLAY;
	ret->ptrglobalvars = ptrglobalvars;
	ret->right = value;
	return ret;
}
Node* createRET(Node* value, Hash* ptrglobalvars){
	Node* ret = createEmptyNode();
	debugmsg(CREATE,"create RET ... ... %p %p",ret, ret->ptrlocalvars);
	ret->op = RET;
	ret->ptrglobalvars = ptrglobalvars;
	ret->left = value;
	return ret;
}

Node* createNOT(Node* expr, Hash * ptrglobalvars){
	Node* ret = createEmptyNode();
	ret->op =  NOT;
	ret->left = expr;
	ret->ptrglobalvars = ptrglobalvars;
	return ret;
}
Node* createIF(Node* expr, Node* thenstmt, Hash *ptrglobalvars){
	Node* ret = createEmptyNode();
	debugmsg(CREATE, "creating if ... ... %p", ret );
	ret->op =  IF;
	ret->left = expr;
	ret->right = thenstmt;
	ret->ptrglobalvars = ptrglobalvars;
	return ret;
}

Node* createIFELSE(Node* expr, Node* thenstmt, Node* elsestmt, Hash *ptrglobalvars){
	Node* ret = createEmptyNode();
	ret->op =  IF;
	ret->left = createNOT(createIF(expr, thenstmt,ptrglobalvars), ptrglobalvars);
	ret->right = elsestmt;
	ret->ptrglobalvars = ptrglobalvars;
	return ret;
}
Node* createComplex(int op, Node* left, Node* right, Hash* ptrglobalvars){
	Node* ret = createEmptyNode();
	debugmsg(CREATE, "creating expr ... ... %p (%s %p %p)",ret, optoStr(op), left,right);
	ret->op =  op;
	ret->left = left;
	ret->right = right;
	ret->ptrglobalvars = ptrglobalvars;
	return ret;
}

Node* createPARAM(char* name, Hash* ptrglobalvars){
	Node* ret = createEmptyNode();
	debugmsg (CREATE, "creating param ... ... %p %s", ret, name );
	ret->op =  PARAMS;
	ret->ptrglobalvars = ptrglobalvars;
	ret->data = createStrData(name);
	return ret;
}

Node* createPARAMS(Node* param, Node* params){
	param->right = params;
	return param;
}

Node* createSTMTS(Node* stmt, Node* stmts, Hash *ptrglobalvars){
	Node* ret = createEmptyNode();
	debugmsg(CREATE,"creating stmts ... ...%p", ret);
	ret->op =  STMT;
	ret->left = stmt;
	ret->right = stmts;
	ret->ptrglobalvars = ptrglobalvars;
	return ret;
}

Node* createWHILE(Node* judge, Node* body, Hash *ptrglobalvars){
	Node* stmts = createSTMTS(body, NULL,ptrglobalvars);
	Node* ret= createIF(judge, stmts, ptrglobalvars);
	ret->ptrglobalvars = ptrglobalvars;
	stmts->right = ret;
	return ret;
}

Node* createFOR(Node* initial, Node* judge, Node* step, Node* body, Hash *ptrglobalvars){
	Node* whilestmt = createWHILE(judge, createSTMTS(body,step,ptrglobalvars),ptrglobalvars);
	return createSTMTS(initial, whilestmt,ptrglobalvars);
}

Node* createFUN(char* name, Node* paramslist, Node* stmts, Hash *ptrglobalvars, Hash *ptrfunhash){
	Node* ret = createEmptyNode();
	debugmsg(CREATE, "creating function ... ... %p param = %p stmts = %p varstable = %p", ret, paramslist, stmts, ptrglobalvars );
	debugmsg(CREATE,"assing op ..." );
	ret->op = FUN;
	debugmsg(CREATE, "assign ptrglobalvars ..." );
	ret->ptrglobalvars = ptrglobalvars;
	debugmsg(CREATE,"assign param ... ...%p", paramslist );
	ret->left = paramslist;
	debugmsg(CREATE,"assign stmts ..." );
	ret->right = stmts;
	debugmsg( CREATE,"done" );
	ret->ptrfuncs = ptrfunhash;

    //after finished a function node, rest the ptr to NULL
	resetcurhash();
	//register the function
//	debugmsg( CREATE,"register function '%s'", name );
//	Data* ptrfun = createPtrData(ret);
//	setItem(*ptrfunhash, name, ptrfun); 
	return ret;
}
Node* createFUNCALL(Hash *funHash, char* name, Node* paramslist, Hash* ptrglobalvars){
	Node* ret = createEmptyNode();
	ret->op = FUNCALL;
	ret->left = paramslist;

    //before modify
//	Data* ptrfun = getItem(*funHash, name);
//	Node* fun = (Node*)ptrfun->value.ptrValue;
//	
//	ret->right = fun;
	//after modify
	ret->right = createStr(name);


	//////////done///
	ret->ptrglobalvars = ptrglobalvars;
	ret->ptrfuncs = funHash;
	return ret;
}

Data Ex(Node* node){
	if(node == NULL) return EMPTY;
	debugmsg(EXECUTE, "Executing %p left:%p right:%p", node, node->left, node->right);
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
		case RET:
			return ExRET(node);
		default:
			return EMPTY;   
	}
	return EMPTY;
}


