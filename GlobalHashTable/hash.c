/*
 * =====================================================================================
 *
 *       Filename:  hash.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/27/2013 09:34:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include "hash.h"

size_t getBKDRHash(const char* input, size_t hashsize){
	size_t hash = 0;
	const char *p = input;
	while (*p){
		hash =  (unsigned int)(*p) + hash*BKDRSEED;
		p++;
	}
	return hash % hashsize;
}

Hash initHash(size_t size){
	Hash ret = (Hash)malloc(sizeof(structHash));
	ret->size = size;
	ret->table = (void**)malloc(sizeof(void*)*size);
	unsigned tmp = size;
	while(tmp>0){
		ret->table[--tmp] = NULL;
	}
	return ret;
}
void freeHash(Hash hash){
	//need to free all items
	free(hash->table);
}

void addItem(Hash hash, const char* name, void* value){
	hash->table[getBKDRHash(name,hash->size)] = value;
}

void removeItem(Hash hash,const char* name){
	hash->table[getBKDRHash(name,hash->size)] = NULL;
}
void* getItem(Hash hash, const char* name){
	return hash->table[getBKDRHash(name, hash->size)];
}


