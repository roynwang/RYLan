/*
 * =====================================================================================
 *
 *       Filename:  objmember.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/18/2013 10:14:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "paramnode.h"
#include "node.h"

Node* createOBJFUN(const char* objname, const char* varname, Node* paramslist);

Node* createOBJVAR(const char* objname, const char* funname, Node* paramslist);

