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
#include <stdio.h>
#include <memory.h>

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
	left = getValue(hash,left);
	right = getValue(hash,right);
	typecheck(left, right);
	if(left->valueType == IntType){
		ret.valueType = IntType;
		ret.value.intValue = left->value.intValue + right->value.intValue;
	}
	if(left->valueType == StrType){

		printf ( "left= %s right = %s\n",left->value.strValue, right->value.strValue );
		ret.valueType = StrType;
		ret.value.strValue = catnewstr(left->value.strValue,right->value.strValue);
		printf ( "result = %s\n", ret.value.strValue );
		ret.isOnHeap = 1;
	}
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
	return ret;
}
char* toString(Data* data){
	if(data->valueType == ArrayType){
		ArrayUnit *au = data->value.arrayValue;
		while(au->data!=NULL){
			printf ( "->>>%p\n",au->data );
			au = au->next;
		}
	}
	return "NEED TO IMPLEMENT toString()\n";
}
Data* createVarData(char* name){
	Data* ret = createEmptyData();
	ret->valueType = VarType;
	ret->value.varValue = name;
	return ret;
}
Data* createStrData(char* value){
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
	printf ( "free data %p type: %d\n",data, data->valueType );
	switch(data->valueType){
		case StrType:
			if(data->isOnHeap == 1)
				free(data->value.strValue);
			break;
		case ArrayType:
			printf ( "free arrary %p\n", data->value.arrayValue );
			freeArray(data->value.arrayValue);
			break;
		default:
			break;
	}
	free(data);
}

