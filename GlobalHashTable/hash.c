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
#include "../debug.h"
#include "../GC/gc.h"

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
    debugmsg(DATASTRUCTURE, "intialize Hash table ... ...");
	Hash ret = (Hash)malloc(sizeof(structHash));
	ret->size = size;
	ret->table = (void**)malloc(sizeof(void*)*size);
	addres(HASHTYPE, ret);
	unsigned int tmp = size;
	while(tmp>0){
		ret->table[--tmp] = NULL;
	}
	return ret;
}
Hash dupHash(Hash hash){
    debugmsg(DATASTRUCTURE, "duplicate Hash table ... ...");
	Hash ret = (Hash)malloc(sizeof(structHash));
	ret->size = hash->size;
	ret->table = (void**)malloc(sizeof(void*)*hash->size);
	unsigned int tmp = hash->size;
	while(tmp>0){
		tmp--;
		ret->table[tmp] = hash->table[tmp];
	}
	return ret;

}
void freeHash(Hash hash){
    debugmsg(FREE, "free Hash table ... ...");
	if(hash == NULL) return;
	//need to free all items
	if(hash->table != NULL){
		free(hash->table);
		hash->table = NULL;
	}
	free(hash);
}

void setItem(Hash hash, const char* name, void* value){

	void* v = hash->table[getBKDRHash(name,hash->size)];
    debugmsg(EXECUTE, "Hash: %p set %s: %p -> %p", hash, name,v, value);
	if(v !=NULL && v!=&EMPTY)
		free(v);
	hash->table[getBKDRHash(name,hash->size)] = value;
}

void removeItem(Hash hash,const char* name){
	hash->table[getBKDRHash(name,hash->size)] = NULL;
}
void* getItem(Hash hash, const char* name){
	if(hash == NULL ) return NULL;
	return hash->table[getBKDRHash(name, hash->size)];
}


