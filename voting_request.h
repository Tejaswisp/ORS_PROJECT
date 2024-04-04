#ifndef HEADER_H
#define HEADER_H
       
//*******************************************Module Description*******************************************************

/*
1. Module name: Voting request module
2. Date: 27-05-2022
3. Function name: voting_request()
3. Author name: Dipa mantre
4. Description: The purpose of this module is to display the voting request menu and call create voting and delete voting function
5. Different functions supported in this module: voting_request()
6. Global variables accessed by module: Count_forms and Forms
*/

//***********************************************************************************************************************

#include"main.h"   //main header file inclusion
#include<string.h>   // for string operations
#include<stdio_ext.h>//for fpurge to clear buffer
#include<ctype.h>

/****************Macros**************************************************************/

#define FIELD_LEN 50
#define FORM_LEN 80
#define ROW_SIZE 30
#define COL_SIZE 30

/***************Structure declaration************************/

typedef struct Voting
{
	char fields[FIELD_LEN];       
	struct Voting *link;
}Vote;

/***************Global variable declarations***************/

int Count_form;	                                             //count of forms created
char Forms[ROW_SIZE][COL_SIZE];	                                    //for storing already created forms

/***************Function declartions**********************/

void voting_request();

#endif 	                                                           //HEADER_H
