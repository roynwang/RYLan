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

void typecheck(Data* left, Data* right){
	if(left->valueType!= right->valueType){
		exit(0);
	}
}
int isInt(Data* data){
	return data->valueType == IntType;
}
int isStr(Data* data){
	return data->valueType == StrType;
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

