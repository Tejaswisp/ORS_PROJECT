//*******************************************Module Description*******************************************************

/*
1. Module name: Training registration module
2. Date: 27-05-2022
3. Function name: send_training_registration_form
3. Author name: Rakshitha S
4. Description: The purpose of this module is to send the  training registration form to enter the user details based on user choice selected from the trainings available
5. Different functions supported in this module: send_training_registration_form()
6. Global variables accessed by module: Forms_count and Forms
7. Modification/History: https://github.com/Harishchiluka0111/Mini_ORS_1_june
*/

//**************************************Header files****************************************

#include<pthread.h>

//*************************************Macro*************************************************

#define THREAD_COUNT 3

//***********************************Function declarations***********************************

void send_training_registration_form();
