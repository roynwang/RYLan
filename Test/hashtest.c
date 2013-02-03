/*
 * =====================================================================================
 *
 *       Filename:  hasttest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/27/2013 09:46:39 PM
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
#include "../GlobalHashTable/hash.h"
#include "../GlobalHashTable/dataunit.h"
#include "../SyntaxNode/node.h"
#include <mcheck.h>

void displaytest(){
	int hashsize = 65536;
	Hash varshash = initHash(hashsize);
	
	setItem(varshash, "int1",createIntData(222));
	setItem(varshash, "int2",createIntData(333));

    Node* node = createDISPLAY(createVar("int1"),&varshash);

	Ex(node);

	freeNode(node);
	freeHash(varshash);
}

void funtest(){

	printf ( "==================fun test=================\n" );
	int hashsize = 65536;
	Hash varshash = initHash(hashsize);
	Hash funhash = initHash(hashsize);
	setItem(varshash, "int1",createIntData(222));
	setItem(varshash, "int2",createIntData(333));

	ArrayUnit * paramlist = (ArrayUnit*)malloc(sizeof(ArrayUnit));
	paramlist->data = createVarData("int1");

	paramlist->next = NULL;

	Node* paramnode = createPARAMS(createPARAM("fParam",&varshash),NULL);

	printf ( "******************1.param test*****************\n" );
	ExPARAMS(paramnode,paramlist);
	printf ( "calculate done\n" );
	Data *p = getItem(varshash, "fParam");
	printf("expected 222    / actual result %d\n",p->value.intValue);

	printf ( "******************2.definiton test*****************\n" );
	// test the function below
	//funtest(fParam){ fParam = fParam + 1;}
	//
	Node* i1 = createVar("fParam");
	Node* i2 = createVar("fParam");
	Node* i3 = createInt(1);
	Node* add = createComplex(ADD, i1, i3, &varshash);
	Node* stmt = createComplex(ASSIGN, i2, add, &varshash); 
	Node* fundef = createFUN("funtest",paramnode,stmt, &varshash,&funhash);	
	printf("expected %p    / actual result %p\n",paramnode, fundef->left);
	printf("expected %p    / actual result %p\n",stmt, fundef->right);

	//register fundef to hash 
//	Data* ptrfun = createPtrData(fundef);
//	setItem(funhash, "funtest", ptrfun);

	printf ( "******************3.call test*****************\n" );

	printf ( "fun = %p \n", fundef );
	// create fun call node;
	Node* call = createFUNCALL(&funhash,"funtest",createArray(paramlist),&varshash);
	Ex(call);
	p = getItem(varshash, "fParam");
	printf("expected 223    / actual result %d\n",p->value.intValue);
	

	printf ( "===========================================\n" );
//	printf ( "%p %p %p %p %p %p %p %p\n",i1,i2,i3,add,stmt,fundef,call );
//    freeHash(varshash);
	printf ( "funhash = %p varshash = %p\n", funhash, varshash );
	freeHash(funhash);
	freeNode(call);
}

void iftest(){
	printf ( "==================if test=================\n" );
	Hash myhash = initHash(65536);

	setItem(myhash, "abc",createIntData(111));
	setItem(myhash, "cde",createIntData(333));


	// if( abc<500) abc = abc + cde
	Node* i1 = createVar("abc");
	Node* i2 = createInt(500);
	Node* i3 = createVar("abc");
	Node* i4 = createVar("abc");
	Node* i5 = createVar("cde");
	printf ( "%p %p %p %p %p\n", i1,i2,i3,i4,i5 );

	Node* add = createComplex(ADD, i4, i5, &myhash);
	Node* stmt = createComplex(ASSIGN, i3, add, &myhash); 
	Node* expr = createComplex(ST, i1, i2, &myhash);
	Node* head = createIF(expr,stmt, &myhash);

	printf ( "%p %p %p %p \n", expr,add,stmt,head);
	Ex(head);
	Data result = *(Data*)getItem(myhash,"abc");
	printf("expected 444    / actual result %d\n",result.value.intValue);

	Ex(head);
	result = *(Data*)getItem(myhash,"abc");
	printf("expected 777    / actual result %d\n",result.value.intValue);
	Ex(head);
	result = *(Data*)getItem(myhash,"abc");
	printf("expected 777    / actual result %d\n",result.value.intValue);

//	freeHash(myhash);
	freeNode(head);

	printf ( "==========================================\n" );
}
void hashtest(){
	printf ( "==================hash test=================\n" );
	//test hash
	size_t hashsize = 65536;
	Hash myhash = initHash(hashsize);

	setItem(myhash, "abc", createStrData("12"));
	setItem(myhash, "cde", createStrData("test"));
	setItem(myhash, "int1",createIntData(222));
	setItem(myhash, "int2",createIntData(333));

	Data* get1 = ((Data*)getItem(myhash,"abc" ));
	Data* get2 = ((Data*)getItem(myhash,"cde" ));
	printf( "abc --%p-- %d --%s\n", get1, get1->valueType, get1->value.strValue);
	printf( "cde --%p-- %d --%s\n", get2, get2->valueType, get2->value.strValue);
	freeHash(myhash);
	printf ( "==========================================\n" );

}
void dataunittest(){

	printf ( "==================data test=================\n" );
	size_t hashsize = 65536;
	Hash myhash = initHash(hashsize);

	setItem(myhash, "abc", createStrData("12"));
	setItem(myhash, "cde", createStrData("test"));
	setItem(myhash, "int1",createIntData(222));
	setItem(myhash, "int2",createIntData(333));

	Data* d1 = createVarData("abc");
	Data* d2 = createVarData("cde");
	Data* d3 = createVarData("int1");
	Data* d4 = createVarData("int2");

	Data result1 = adddata(myhash, d1,d2);
	Data result2 = adddata(myhash, d3,d4);
	printf("expected 12test / actual result %s\n",result1.value.strValue);
	printf("expected 555    / actual result %d\n",result2.value.intValue);
	freeHash(myhash);
	freeData(d1);
	freeData(d2);
	freeData(d3);
	freeData(d4);
	free(result1.value.strValue);
	printf ( "============================================\n" );
}
void nodetest(){

	Hash myhash = initHash(65536);
	printf ( "==================Node test=================\n" );

	Data* d1 = (Data*)malloc(sizeof(Data));
	Data* d2 = (Data*)malloc(sizeof(Data));
	Data* d3 = (Data*)malloc(sizeof(Data));
	Data* d4 = (Data*)malloc(sizeof(Data));

	d1->valueType = VarType;
	d1->value.varValue = "abc";

	d2->valueType = VarType;
	d2->value.varValue = "cde";

	d3->valueType = VarType;
	d3->value.varValue = "int1";

	d4->valueType = VarType;
	d4->value.varValue = "int2";


	Node* head = (Node*)malloc(sizeof(Node));
	head->op = ADD;
	head->ptrlocalvars = &myhash;
	head->data = NULL;

	Node* left = (Node*)malloc(sizeof(Node));
	Node* right = (Node*)malloc(sizeof(Node));
	head->left = left;
	head->right = right;

	left->op = GET;
	left->data = d3;
	left->ptrlocalvars = &myhash;
	right->op = GET;
	right->data = d4;
	right->ptrlocalvars = &myhash;

	Data result3 = Ex(head);
	printf("expected 555    / actual result %d\n",result3.value.intValue);


	Node* nested = (Node*)malloc(sizeof(Node));
	nested->op = ASSIGN;
	nested->left  = left; 
	nested->right = head;
	nested->ptrlocalvars = &myhash;
	Ex(nested);
	result3 = *(Data*)getItem(myhash,"int1");
	printf("expected 555    / actual result %d\n",result3.value.intValue);
	Ex(nested);
	result3 = *(Data*)getItem(myhash,"int1");
	printf("expected 888    / actual result %d\n",result3.value.intValue);

	left->data = d1;
	right->data = d2;

	result3 = Ex(head);
	printf("expected 12test / actual result %s\n",result3.value.strValue);
	printf ( "============================================\n" );
//	freeHash(myhash);
	freeNode(head);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	mtrace();
	funtest();
	hashtest();
	dataunittest();
	iftest();
//    nodetest();
	displaytest();
    
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
