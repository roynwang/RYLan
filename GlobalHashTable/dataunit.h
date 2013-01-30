/*
 * =====================================================================================
 *
 *       Filename:  dataunit.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/28/2013 07:26:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  DATAUNIT_INC
#define  DATAUNIT_INC

#include "hash.h"

#define TRUE trueData
#define FALSE falseData

typedef struct _ArrayUnit{
	void* data;
	struct _ArrayUnit * next;	
} ArrayUnit;

typedef enum { IntType, StrType, VarType, True, False, Empty, ArrayType} TypeEnum;
typedef struct _Data{
	int valueType;
	union {
		const char* strValue;
		int intValue;
		const char* varValue;
		ArrayUnit* arrayValue;
	}value;
}Data;

Data trueData ;
Data falseData;

Data* createIntData(int value);
Data* createStrData(char* value);
Data* createVarData(char* name);
Data* createArrayData(ArrayUnit* arr);

Data adddata(Hash hash, Data* left, Data* right);
Data subdata(Hash hash, Data* left, Data* right);
Data muldata(Hash hash, Data* left, Data* right);
Data divdata(Hash hash, Data* left, Data* right);
Data comparedata(Hash hash, Data* left, Data* right);
Data* createEmptyData();
char* toString(Data* data);
int isTrue(Data* data);
#endif   /* ----- #ifndef DATAUNIT_INC  ----- */
