/*****************************************DESCRIPTION*******************************************************************/
/*

1. Name of the module                           : feedback_module
2. Date of creation                             : 27/5/2022
3. Author of Module                             : Tejaswini S P
4. Description of module                        : The purpose of this module is to display the conducted trainings and after the user selects the particular training it will call the feedback function to record the user given feedback
 
5. Different functions supported in this module : feedback_module()
6.Github link                                   : https://github.com/Harishchiluka0111/Mini_ORS_1_june
*/

/**********************************************************************************************************************/

/**************************HEADER FILES*****************************/
#include"main.h"
#include<string.h>
#include<dirent.h>
#include<stdio_ext.h>

/***************************Macros*********************************/
#define ROW_LEN 50
#define COL_LEN 50

/************************Global variables**************************/

char Training_form_name[ROW_LEN][COL_LEN]; //2d-array to store conducted training names

/*************************FUNCTION PROTOTYPES**********************/
void feedback_module();  //display the available conducted training forms and calls the feedback function to give feedback for the selected training form          
