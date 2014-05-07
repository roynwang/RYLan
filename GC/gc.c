/*
 * =====================================================================================
 *
 *       Filename:  gc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/09/2013 09:18:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "gc.h"
#include "../debug.h"
void addres(char restype, void *res){

	DataRes* unit = (DataRes*)malloc(sizeof(DataRes));
	if(restype == DATATYPE){
		unit->data.datares = res;
		unit->next = datares->res;
		datares->res = unit;
		debugmsg(FREE, "add resource DATA... ... %p", datares->res);
	}
	else if(restype == NODETYPE){
		unit->data.noderes = res;
		unit->next = noderes->res;
		noderes->res = unit;
		debugmsg(FREE, "add resource NODE... ... %p", noderes->res);
	}
	else if(restype == HASHTYPE){
		unit->data.hashres = res;
		unit->next = hashres->res;
		hashres->res = unit;
		debugmsg(FREE, "add resource Hash... ... %p", hashres->res);
	}
}

void initialGC(){
	datares = (Resource*)malloc(sizeof(Resource));
	datares->res = NULL;
	noderes = (Resource*)malloc(sizeof(Resource));
	noderes->res = NULL;
	hashres = (Resource*)malloc(sizeof(Resource));
	hashres->res = NULL;
}

void finializeMem(){

	DataRes* dr = datares->res;
	while(dr != NULL){
		DataRes* tmp = dr;
		dr = dr->next;
		freeData(tmp->data.datares);
//		debugmsg(FREE,"next ... ...%p", tmp->data.datares);
		free(tmp);
	}
	debugmsg(FREE,"free DATA done");

	dr = noderes->res;
	debugmsg(FREE,"free NODE ... ...%p", dr);
	while(dr != NULL){
		DataRes* tmp = dr;
		dr = dr->next;
		freeNode(tmp->data.noderes);
//		debugmsg(FREE,"next ... ...%p", tmp->data.noderes);
		free(tmp);
	}
	debugmsg(FREE,"free NODE done");

	dr = hashres->res;
	while(dr != NULL){
		DataRes* tmp = dr;
		dr = dr->next;
		freeHash(tmp->data.hashres);
//		debugmsg(FREE,"next ... ...%p", tmp->data.noderes);
		free(tmp);
	}
	debugmsg(FREE,"free HASH done");

}


