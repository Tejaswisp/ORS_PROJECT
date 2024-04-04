
/****************************************DESCRIPTION***********************************************************************/

/*
   1. Name of thie module                          : Voting Response Module
   2. Date of creation                             : 27/5/2022
   3. Author of Module                             : Sindhushree J M
   4. Description of module                        : The purpose of this module is to collect voting response from the users for the voting request conducted, then it is 
                                                     recorded in the excel form created.
   5. Different functions supported in this module : voting_response()	
   6. Global variables accessed/modified by module : Count_forms, Forms, Form_option
   7. Revision/Modification History                : https://github.com/Harishchiluka0111/Mini_ORS_1_june
   */

/**************************************************************************************************************************/


/**************************HEADER FILES*****************************/
#include"main.h"                            //Inclusion of main function header
#include<pthread.h>                        //Inclusion of pthread header for creating pthreads
#include"voting_request.h"                //Inclusion of voting request header for accessing global variables
#include<dirent.h>
/***************FUNCTION PROTOTYPES*********************************/                  
void voting_response();                 //This function used to collect voting response from the three users for the voting request conducted by creating three threads.

