/*
 * =====================================================================================
 *
 *       Filename:  hash.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/27/2013 09:33:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stddef.h>
//for BKDR hash
#define BKDRSEED 131; // the magic number, 31, 131, 1313, 13131, etc.. 
typedef struct {
	size_t size;
	void** table;
} Hash;

size_t getBKDRHash(const char* input, size_t hashsize);

Hash initHash(size_t size);
void freeHash(Hash *hash);

void addItem(Hash hash, const char* name, void* value);
void removeItem(Hash hash, const char* name);
void* getItem(Hash hast, const char* name);
