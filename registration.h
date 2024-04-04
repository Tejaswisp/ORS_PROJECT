//*******************************************Module Description*******************************************************

/*
1. Module name: Training registration module
2. Date: 27-05-2022
3. Author name: Rakshitha S
4. Description: The purpose of this function is to provide user choice for create training registration form, delete training registration form and send training registration form. Based on user input, the function will be called.
5. Different functions supported in this module: registration(), create_training_registration_form, delete_training_registration_form and Send_training_registration form
6. Global variables accessed by module: Forms_count and  Forms
7. Modification/History: https://github.com/Harishchiluka0111/Mini_ORS_1_june
*/

//**************************************Header files****************************************

#include"main.h"
#include<string.h>
#include<dirent.h>

//*************************************Macro*************************************************

#define ROW_SIZE 30
#define COL_SIZE 30
#define MAX_LEN 80

//***********************************Structure declaration*************************************

typedef struct employee_data
{
    char fields[COL_SIZE];
    struct employee_data *link;
}Employee_training_data;

//***********************************Global variables*******************************************

int Forms_count; //Variable to store count of training registration forms created
char Form[ROW_SIZE][COL_SIZE]; //2d-array to store names of trainings
int Entry_count;
//***********************************Function declarations*****************************************

void registration();
