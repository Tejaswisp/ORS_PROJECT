#define _GNU_SOURCE

//Header files inclusion
#include"voting_response.h"

/******************************Function definition of voting_response()***************************************************************************/

pthread_mutex_t lock;                                                            //mutex lock declarartion
int Form_option;

void *thread_handler(void *Forms)
{
	pthread_mutex_lock(&lock);                                               //acquiring the lock

	char *form = (char *)Forms;                                              //typecasting void * to char*
	FILE *file_pointer1 = fopen(form, "r");                                  //opens a particular file in read mode
	char buffer_id[ROW_SIZE][COL_SIZE], buffer1_id[ROW_SIZE][COL_SIZE];      //buffers for storing all user id's
	int i = 0, j = 0; 	                                                 //for storing index value of Buffers

	//For copying all user id's to one buffer from file pointer
	while(!feof(file_pointer1))                                              //loop until it reaches end of file
	{
		fscanf(file_pointer1, "%s\t", buffer_id[i]);                     //reading all content file to buffer
		if(buffer_id[i][0] =='0')                                        //checking whether fields have id
		{
			strcpy(buffer1_id[j], buffer_id[i]);                     //if id present copy all id's to another buffer
			j++;
		}
		i++;
	}                                              
	rewind(file_pointer1);

	//For copying all the created fields of a particular form to one buffer
	char buffer_field[ROW_SIZE][COL_SIZE];
	int field_index = 0, field_index1 = 0;
	while(!feof(file_pointer1))
	{
		fscanf(file_pointer1, "%[^\t]%*c", buffer_field[field_index1]);
		if(strchr(buffer_field[field_index1],'\n') != NULL)
		{
			break;
		}
		field_index1++;
	}
	fclose(file_pointer1);                                                   //close file opened in read mode

	FILE *file_pointer = fopen(form, "a");                                   //opens a particular form in append mode 
	char buffer[ROW_SIZE][COL_SIZE];                                         //Buffer to store the user details after every thread execution
	int buf_index = 0;                                                       //To store index value of buffers
	int invalid_option1 = 0, invalid_option2 = 0, invalid_option3 = 0, invalid_option4 = 0, invalid_option5 = 0;

	while(field_index < field_index1)                                       //Looping untill field_index reaches all created fields
	{
		char *str = (char*)malloc(MAX_LEN * sizeof(char));              //To take user inputs for created fields
		printf("Enter %s: ", buffer_field[field_index]);
		__fpurge(stdin);
		scanf("%[^\n]%*c", str);

		if(strcasestr(buffer_field[field_index], "mail") != NULL)       //condition to check user created fields has employee mail id
		{
			int i = 0, flag = 0, flag1 = 0;
			if(str[0] >= 97 && str[0] <= 122)                       //condition to check user entered mail id starts with lower case letter
			{
				while(str[i] != '@')
				{
					if(str[i] == '.' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))  //condition to check whether mail-id has only letters and ., no special characters
					{
						if(str[i] == '.')
						{
							if(flag1 == 0)
							{
								flag1 = 1;
								i++;
							}
							else
							{
								flag = 1;
								break;
							}
						}
						else
						{
							i++;
							flag1 = 0;
						}
					}
					else
					{
						flag = 1;
						break;
					}
				}
			}
			else
			{
				flag = 1;
			}
			if(flag == 0 && (strstr(str, "@thundersoft.com") != NULL))        //Condition to check whether Email-id has @thundersoft.com
			{
				strcpy(buffer[buf_index], str);                          //copying user input to buffer
				field_index++;                                            //move to next field
				buf_index++;                                             //incrementing value of buffer index
				free(str);
				continue;                                               //will check the condition again for next filed
			}
			else
			{
				invalid_option1++;
				if(invalid_option1 != 3)                                //checks for invalid option count is not equal to 3
				{
					printf("\nINFO: Please enter valid %s\n\n", buffer_field[field_index]);
					free(str);                                     //free allocated memory
					continue;
				}
				else
				{
					printf("\nError : User entered invalid %s three times\n\n", buffer_field[field_index]);
					fclose(file_pointer);          //closes a file
					pthread_mutex_unlock(&lock);  //releases the acquired lock
					pthread_exit(NULL);           //terminates a thread
				}
			}
		}

		else if(strcasestr(buffer_field[field_index], "id") != NULL)            //condition to check user created fields has employee id
		{
			int flag = 0, flag1 = 0, i = 0;
			for(int i = 0;i < j;i++)                                        //To check Employee-id is already present or not
			{
				if(strcmp(str, buffer1_id[i]) == 0)
				{
					flag = 1;
					break;
				}
			}
			if(str[0] == '0' && str[1] == '2')                             //condition to check employee id starts with 0 and then 2
			{
				while(str[i] != '\0')
				{
					if(str[i] >= 48 && str[i] <= 57)             //Condition to check Employee id has special characters
					{
						i++;
					}
					else
					{
						flag1 = 1;
						break;
					}
				}
			}
			else
			{
				flag1 = 1;
			}
			if(flag == 0)
			{
				if(flag1 == 0 && i > 6)
				{
					strcpy(buffer[buf_index], str);                          //copying user input to buffer
					field_index++;                                          //move to next field
					buf_index++;                                           //incrementing value of buffer index
					free(str);
					continue;                                               //will check the condition again for next filed
				}
				else
				{
					invalid_option2++;
					if(invalid_option2 != 3)                                //checks for invalid option count is not equal to 3
					{
						printf("\nINFO: Please enter valid %s\n\n", buffer_field[field_index]);
						free(str);                                     //free the allocated memory
						continue;
					}
					else
					{
						printf("\nError: User enetered invalid %s three times\n\n", buffer_field[field_index]);
						fclose(file_pointer);            //for closing file
						pthread_mutex_unlock(&lock);    //for releasing the lock acquired
						pthread_exit(NULL);             //terminates the thread execution
					}

				}
			}
			else
			{
				printf("\nINFO: Current user already given response\n\n");
				fclose(file_pointer);         //closes a file
				pthread_mutex_unlock(&lock); //To release the lock acquired
				pthread_exit(NULL);          //terminating the thread execution
			}
		}

		else if(strcasestr(buffer_field[field_index], "contact") != NULL)        //condition to check user created fields has  contact field
		{
			int i = 0, flag = 0;
			if(str[0] >= 54 && str[0] <= 57)                                 //checks for starting number is 6,7,8
			{
				while(str[i] != '\0')                              
				{
					if(str[i] >= 48 && str[i] <= 57)                //checks for only numeric
					{
						i++;
					}
					else
					{
						flag = 1;
						break;
					}
				}
			}
			if(flag == 0 && i == 10)                                      //checks for contact number count equal to 10
			{
				strcpy(buffer[buf_index], str);
				buf_index++;
				field_index++;
				free(str);
				continue;
			}
			else
			{
				invalid_option3++;
				if(invalid_option3 != 3)                            //checks for count of invalid option not equal to 3
				{
					printf("\nError: Please enter valid %s\n\n", buffer_field[field_index]);
					free(str);
					continue;
				}
				else
				{
					printf("\nError: User enetered invalid %s three times\n\n", buffer_field[field_index]);
					fclose(file_pointer);                //closes a file
					pthread_mutex_unlock(&lock);        //releases the lock acquired
					pthread_exit(NULL);                //terminates the thread execution
				}
			}
		}

		else if(strcasestr(buffer_field[field_index], "experience") != NULL)                    //To take user inputs for experience
		{
			int i = 0, flag = 0;

			if(str[0] >=48 && str[0] <= 57)                                                 //To check valid conditions for experience
			{
				while(str[i] != '\0')
				{
					if(str[i] >= 48 && str[i] <=57)
					{
						i++;
					}
					else
					{
						flag = 1;
						break;
					}
				}
			}
			//To store user data to buffer
			if(flag == 0 && i == 2)
			{
				strcpy(buffer[buf_index], str);
				buf_index++;
				field_index++;
				free(str);
				continue;
			}
			else
			{
				invalid_option5++;
				if(invalid_option5 != 3)
				{
					printf("\nError: Please enter valid experience in years\n\n");
					free(str);
					continue;
				}
				else
				{
					printf("\nError: User enetered invalid %s three times, terminating the thread execution\n\n", buffer_field[field_index]);
					fclose(file_pointer); //To close file
					pthread_mutex_unlock(&lock); //To release the lock acquired
					pthread_exit(NULL); //To terminate the thread execution
				}
			}
		}

		else
		{
			int i = 0, flag = 0, flag1 = 0;
			while(str[i] != '\0')                                                            
			{
				if(str[i] == ' ' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) //To check string has no special characters other than space
				{
					if(str[i] == ' ')
					{
						if(flag1 == 0)
						{
							flag1 = 1;
							i++;
						}
						else
						{
							flag = 1;
							break;
						}
					}
					else
					{
						i++;
						flag1 = 0;
					}
				}
				else
				{
					flag = 1;
					break;
				}
			}

			if(i >= FIELD_LEN)        //Condition to check whether buffer size is not more than field length set
			{
				printf("\nError: Buffer exceeded\n\n");
				free(str);        //free the allocated memory
				continue;
			}
			if(flag == 0)
			{
				strcpy(buffer[buf_index], str);                          //copying user input to buffer
				field_index++;                                           //move to next field
				buf_index++;                                             //incrementing value of buffer index
				free(str);                                              //free the allocated memory
				continue;                                               //will check the condition again
			}
			else
			{
				invalid_option4++;
				if(invalid_option4 != 3)                                //checks for invalid option count is not equal to 3
				{
					printf("\nError: No special characters are allowed\n\n");
					free(str);                                     //free the allocated memory
					continue;
				}
				else
				{
					printf("\nError: User enetered invalid %s three times\n\n", buffer_field[field_index]);
					fclose(file_pointer);            //closes a file
					pthread_mutex_unlock(&lock);     //releases the lock acquired
					pthread_exit(NULL);             //terminates the thread execution
				}
			}
		}
	}

	printf("\nInfo: Employee details are recorded successfully\n\n");         //To store the employee details to excel sheet
	for(int i = 0;i < buf_index;i++)
	{
		fprintf(file_pointer, "%s\t", buffer[i]);
	}
	fprintf(file_pointer, "\n");
	fclose(file_pointer);                                                    //closes a file
	pthread_mutex_unlock(&lock);                                             //releases the acquired lock
}

void voting_response()
{
	struct dirent *directory_entry;               //Creating a pointer of type struct dirent to point to pwd
	DIR *dr = opendir(".");                       //opening a present working directory

	int flag = 0, count = 0;                     //local variables declaration

	if(dr == NULL)                               //checks for directory open success or not
	{
		printf("\nError: Opening a directory is not successfull\n\n");
	}

	while((directory_entry = readdir(dr)) != NULL)      //loop to check _request forms in pwd
	{
		if(strstr(directory_entry->d_name, "_request.xlsx") != NULL) //search for voting_request forms in a directory
		{
			if(Count_form == 0)
			{
				strcpy(Forms[Count_form], directory_entry->d_name);     //copy the voting_requrest forms to Forms array to dispaly all voting forms
				Count_form++;
			}
			else
			{
				for(int i = 0;i < Count_form;i++)                       //loop to check for duplicates of voting_request forms 
				{
					if(strcasecmp(Forms[i], directory_entry->d_name) == 0)  //compares already copied _request forms with directoty forms
					{
						flag = 1;
						break;                                         //if particular voting form already present break the loop
					}
				}
				if(flag == 0)                                                  
				{
					strcpy(Forms[Count_form], directory_entry->d_name);  //copy _request forms only if forms array doesn't have particular form of directory
					Count_form++;
				}
			}

		}
	}
	closedir(dr);  //closes a opened directory

	if(Count_form > 0)
	{

		printf("\nAvailable voting forms are: \n");
		for(int i = 0;i < Count_form;i++)                          //loop to print all available voting forms in pwd
		{
			printf("%d. %s\n", i+1, Forms[i]);
		}
		while(1)
		{
			char choice;
			printf("Please select from available voting forms for providing response : ");
			__fpurge(stdin);   //clear input buffer
			scanf("%d", &Form_option);
			if(Form_option <= Count_form && Form_option != 0)   //checks for selected form number is less than total available forms 
			{
				pthread_t thread;  //Declaring a thread of type pthread_t 
				do
				{
					pthread_create(&thread, NULL, thread_handler, (void *)Forms[Form_option - 1]);   //creating a thread with thread handler function
					pthread_join(thread, NULL); //To wait until particular thread termaination
					printf("Do you want to enter any other employee details[y/n]? ");
					__fpurge(stdin);  //clear input buffer
					scanf("%c", &choice);
				}while(choice == 'y' || choice == 'Y');  //loop run untill user enters no option
				voting();  //calling previous menu

			}
			else
			{
				count++;
				if(count != 3)         //checks for count of invalid option 
				{
					printf("\nINFO: Please enter a valid option\n\n");
				}
				else
				{
					printf("\nError: User entered invalid option for three times, returning to previous menu\n\n");
					voting();   //calling previous menu
				}
			}
		}
	}
	else
	{
		printf("\nINFO: No voting forms available\n\n");
		voting();  //calling previous menu
	}
}

