/*
 * =====================================================================================
 *
 *       Filename:  dataunit.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/28/2013 07:29:06 PM
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
#include "dataunit.h"
#include <memory.h>
#include "../debug.h"
#include "../GC/gc.h"

Data trueData = {valueType: True};
Data falseData = {valueType: False};
Data emptyData = {valueType: Empty}; 

char* catnewstr(const char* a, const char* b){
	int lena = strlen(a);
	int lenb = strlen(b);
	char* ret = (char*)malloc(sizeof(lena+lenb+1));
	char* start = ret;
	memcpy(ret, a, lena);
	ret+=lena;
	memcpy(ret, b, lenb);
	ret+=lenb;
	*ret='\0';
	return start;
}


void typecheck(Data* left, Data* right){
	debugmsg(EXECUTE,"type checking ... ... %s %s", toString(left), toString(right) );
	if(left->valueType!= right->valueType){
		exit(0);
	}
}
int isInt(Data* data){
	return data->valueType == IntType ? 1:0;
}
int isStr(Data* data){
	return data->valueType == StrType ? 1:0;
}
Data* getValue(Hash hash, Data* data){
	if(data->valueType == VarType){
		return (Data*)getItem(hash, data->value.varValue);
	}
	return data;
}
Data adddata(Hash hash, Data* left, Data* right){
	Data ret;
	debugmsg(EXECUTE,"ADD DATA ... ...");
	left = getValue(hash,left);
	right = getValue(hash,right);
	typecheck(left, right);
	if(left->valueType == IntType){
		ret.valueType = IntType;
		ret.value.intValue = left->value.intValue + right->value.intValue;
		debugmsg(EXECUTE,"ADD RESULT %d", ret.value.intValue);
	}
	if(left->valueType == StrType){
		ret.valueType = StrType;
		ret.value.strValue = catnewstr(left->value.strValue,right->value.strValue);
		ret.isOnHeap = 1;
	}
	debugmsg (EXECUTE, "DONE ... ..." );
	return ret;
}
Data subdata(Hash hash, Data* left, Data* right){
	left = getValue(hash,left);
	right = getValue(hash,right);
	if(!isInt(left) || !isInt(right))
		exit(0);
	//		Error("'-' is only accepted between to number\n");

	Data ret;
	ret.valueType = IntType;
	ret.value.intValue = left->value.intValue - right->value.intValue;
	return ret;
}
Data muldata(Hash hash, Data* left, Data* right){
	left = getValue(hash,left);
	right = getValue(hash,right);
	if(!isInt(left) || !isInt(right))
		exit(0);
	//		Error("'*' is only accepted between to number\n");
	Data ret;
	ret.valueType = IntType;
	ret.value.intValue = left->value.intValue * right->value.intValue;
	return ret;
}
Data divdata(Hash hash, Data* left, Data* right){
	left = getValue(hash,left);
	right = getValue(hash,right);
	if(!isInt(left) || !isInt(right))
		exit(0);
	//		Error("'/' is only accepted between to number\n");
	Data ret;
	ret.valueType = IntType;
	ret.value.intValue = left->value.intValue / right->value.intValue;
	free(left);
	free(right);
	return ret;
}
Data comparedata(Hash hash, Data* left, Data* right){
	Data ret;
	ret.valueType = Empty;
	left = getValue(hash,left);
	right = getValue(hash,right);
	if(!isInt(left) || !isInt(right))
		exit(0);
	if(left->value.intValue<right->value.intValue){
		ret.value.intValue = -1;
	}
	else if(left->value.intValue>right->value.intValue)
		ret.value.intValue = 1;
	else
		ret.value.intValue = 0;
	return ret;
}
Data* createEmptyData(){
	Data* ret = (Data*)malloc(sizeof(Data));
	ret->valueType = Empty;
	ret->isOnHeap = 0;
	addres(DATATYPE, ret);
	return ret;
}
char* toString(Data* data){
	if(data == NULL) return "NULL";
	switch(data->valueType){
		case VarType:
			return "Var";
		case ArrayType:
			return "Array";
		case StrType:
			return "String";
		case IntType:
			return "Integer";
		case PtrType:
			return "Pointer";
		case True:
			return "True";
		case False:
			return "False";
		case Empty:
			return "Empty";
		default:
			break;
	}
	return "ERROR";
}
Data* createVarData(char* name){
	Data* ret = createEmptyData();
	ret->valueType = VarType;
	ret->value.varValue = name;
	return ret;
}
Data* createStrData(const char* value){
	Data* ret = createEmptyData();
	ret->valueType = StrType;
	ret->value.strValue  = value;
	return ret;
}
Data* createIntData(int value){
	Data* ret = createEmptyData();
	ret->valueType = IntType;
	ret->value.intValue = value;
	return ret;
}
Data* createArrayData(ArrayUnit *arr){
	Data* ret = createEmptyData();
	ret->valueType = ArrayType;
	ret->isOnHeap = 1;
	ret->value.arrayValue = arr;
}
Data* createPtrData(void* value){
	Data* ret = createEmptyData();
	ret->valueType = PtrType;
	ret->isOnHeap = 1;
	ret->value.ptrValue = value;
}
ArrayUnit* createArrayUnit(Data* value){
	ArrayUnit* tmp = (ArrayUnit*)malloc(sizeof(ArrayUnit));
	tmp->data = value;
	tmp->next = NULL;
	return tmp;
}

int isTrue(Data* data){
	return data->valueType == True? 1:0;
}

void freeArray(ArrayUnit* arr){
	while(arr!= NULL){
		freeData((Data*) arr->data);
		ArrayUnit* tmp = arr->next;
		free(arr);
		arr = tmp;
	}
}
void freeData(Data* data){
	debugmsg(FREE, "free data %p",data, data->valueType );
	switch(data->valueType){
		case StrType:
			if(data->isOnHeap == 1)
				free(data->value.strValue);
			break;
		case ArrayType:
			freeArray(data->value.arrayValue);
			break;
		default:
			break;
	}
	free(data);
}

