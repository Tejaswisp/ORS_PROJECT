/*****************************************DESCRIPTION*******************************************************************/
/*

1. Name of the module                           : feedback
2. Date of creation                             : 27/5/2022
3. Author of Module                             : Tejaswini S P
4. Description of module                        : The purpose of this module is to take the feedback from the user

5. Different functions supported in this module : feedback(int)
6.Github link                                   : https://github.com/Harishchiluka0111/Mini_ORS_1_june
*/

/**********************************************************************************************************************/

/**************************HEADER FILES*****************************/
#include<pthread.h>

/************************MACROS**********************************/
#define FIELD_LEN 80
#define MAX_SIZE 256

/*************************structure for this module**************/
typedef struct employee_f
{
char emp_id[FIELD_LEN];
char emp_name[FIELD_LEN];
char emp_email[FIELD_LEN];
char reporting_mgr[FIELD_LEN];
char feedback[MAX_SIZE];
}Employee_training_feedback;


/*************************FUNCTION PROTOTYPES**********************/
void feedback(int option);  //to record the feedback from the user for the conducted trainings and store the data in the .xlsx file
