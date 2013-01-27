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
#include "hash.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	const size_t hashsize = 65536;
	Hash myhash = initHash(hashsize);
	int abc = 12;
	char* cde = "test";
	addItem(myhash, "abc", &abc);
	addItem(myhash, "cde", &cde);
	printf("Item abc = %d\n",*((int*)getItem(myhash, "abc")));
	printf("Item cde = %s\n",*((char**)getItem(myhash,"cde")));
	freeHash(myhash);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
