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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	printf ( "==================hash test=================\n" );
	//test hash
	const size_t hashsize = 65536;
	Hash myhash = initHash(hashsize);
	char* abc = "12";
	char* cde = "test";
	Data* v1 = (Data*)malloc(sizeof(Data));
	Data* v2 = (Data*)malloc(sizeof(Data));
	Data* v3 = (Data*)malloc(sizeof(Data));
	Data* v4 = (Data*)malloc(sizeof(Data));
	v1->value.strValue = abc;
	v1->valueType = StrType;
	v2->value.strValue = cde;
	v2->valueType = StrType;

	v3->value.intValue = 222;
	v3->valueType = IntType;
	v4->value.intValue = 333;
	v4->valueType = IntType;

	setItem(myhash, "abc", v1);
	setItem(myhash, "cde", v2);
	setItem(myhash, "int1",v3);
	setItem(myhash, "int2",v4);
	
	Data* get1 = ((Data*)getItem(myhash,"abc" ));
	Data* get2 = ((Data*)getItem(myhash,"cde" ));
	printf( "abc --%p-- %d --%s\n", get1, get1->valueType, get1->value.strValue);
	printf( "cde --%p-- %d --%s\n", get2, get2->valueType, get2->value.strValue);

	//test dataunit
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

	Data result1 = adddata(myhash, d1,d2);
	Data result2 = adddata(myhash, d3,d4);
	printf("expected 12test / actual result %s\n",result1.value.strValue);
	printf("expected 555    / actual result %d\n",result2.value.intValue);

	printf ( "============================================\n" );
	printf ( "==================Node test=================\n" );

	Node* head = (Node*)malloc(sizeof(Node));
	head->op = ADD;
	head->localvars = myhash;

	Node* left = (Node*)malloc(sizeof(Node));
	Node* right = (Node*)malloc(sizeof(Node));
	head->left = left;
	head->right = right;
	
	left->op = GET;
	left->data = d3;
	right->op = GET;
	right->data = d4;

	Data result3 = Ex(head);
	printf("expected 555    / actual result %d\n",result3.value.intValue);
	

	Node* nested = (Node*)malloc(sizeof(Node));
	nested->op = ASSIGN;
	nested->left  = left; 
	nested->right = head;
	nested->localvars = myhash;
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
	freeHash(myhash);
	freeNode(head);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
