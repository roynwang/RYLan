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

typedef enum { IntType, StrType, VarType} TypeEnum;
typedef struct {
	int valueType;
	union {
		int intValue;
		char* strValue;
		char* varValue;
	} value;
}Data;

Data adddata(Hash hash, Data* left, Data* right);
Data subdata(Hash hash, Data* left, Data* right);
Data muldata(Hash hash, Data* left, Data* right);
Data divdata(Hash hash, Data* left, Data* right);

#endif   /* ----- #ifndef DATAUNIT_INC  ----- */
