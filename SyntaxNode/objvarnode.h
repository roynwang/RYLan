/*
 * =====================================================================================
 *
 *       Filename:  objvarnode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2013 11:22:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  OBJVARNODE_INC
#define  OBJVARNODE_INC

#include "node.h"

Node* createOBJVAR(char* objname, char* varname);

Data ExOBJVAR(Node* node);

#endif   /* ----- #ifndef OBJVARNODE_INC  ----- */
