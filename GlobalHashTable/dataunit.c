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

Data trueData = {valueType: True};
Data falseData = {valueType: False};


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
		ret.valueType = StrType;
		char* str = (char*)malloc(sizeof(char)*(strlen(left->value.strValue)+strlen(right->value.strValue)+1));
		ret.value.strValue = strcat(strcat(str, left->value.strValue),right->value.strValue);
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
	return ret;
}
char* toString(Data* data){
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
	ret->value.arrayValue = arr;
	
}

int isTrue(Data* data){
	return data->valueType == True? 1:0;
}


