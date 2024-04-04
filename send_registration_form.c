#define _GNU_SOURCE

#include"registration.h"
#include"send_registration_form.h"

//*******************************************Send registration form**********************************************

pthread_mutex_t lock;

void *thread_handler_1(void *Forms)
{
	pthread_mutex_lock(&lock); //Acquiring lock
        char *form = (char *)Forms;

	char buffer[ROW_SIZE][COL_SIZE];
	FILE *file_pointer1 = fopen(form, "r"); //To open file in read mode
	int index = 0,i = 0, j = 0, field_index = 0, field_index1 = 0;
	int invalid_email = 0, invalid_id = 0, invalid_name = 0, invalid_contact = 0, invalid_exp = 0;
	char buffer_id[ROW_SIZE][COL_SIZE], buffer1_id[ROW_SIZE][COL_SIZE], buffer_field[ROW_SIZE][COL_SIZE]; //2D-array declaration
	

	//To store all employee id into one buffer
	while(!feof(file_pointer1))
	{
		fscanf(file_pointer1, "%s\t", buffer_id[i]);
		if(buffer_id[i][0] == '0')
		{
			strcpy(buffer1_id[j], buffer_id[i]);
			j++;
		}
		i++;
	}
	rewind(file_pointer1); //To move file offset to 0
	//To store fields into buffer
	while(!feof(file_pointer1))
	{
		fscanf(file_pointer1, "%[^\t]%*c", buffer_field[field_index]);
		if(strchr(buffer_field[field_index],'\n') != NULL)
		{
			break;
		}
		field_index++;
	}

			
	fclose(file_pointer1); //To close file

	FILE *file_pointer = fopen(form, "a"); //To open file in append mode
	//To take user input for employee details
	while(field_index1 < field_index)
	{
		char *data = (char *)malloc(MAX_LEN * sizeof(char));
		printf("Enter %s: ", buffer_field[field_index1]);
		__fpurge(stdin);
		scanf("%[^\n]%*c", data);

		//To take user inputs for Email-id
		if(strcasestr(buffer_field[field_index1], "mail") != NULL) 
		{
			int index1 = 0, flag = 0, flag1 = 0;
			//To check for valid conditions of Email-id
			if(data[0] >= 97 && data[0] <= 122)
			{
				while(data[index1] != '@')
				{
					if(data[index1] == '.' || (data[index1] >= 65 && data[index1] <= 90) || (data[index1] >= 97 && data[index1] <= 122))
					{
						if(data[index1] == '.')
                                                {
                                                        if(flag1 == 0)
                                                        {
                                                                flag1 = 1;
                                                                index1++;
                                                        }
                                                        else
                                                        {
                                                                flag = 1;
                                                                break;
                                                        }
                                                }
                                                else
                                                {
                                                        index1++;
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

			//Condition to check whether Email-id has @thundersoft.com
			if(flag == 0 && (strstr(data, "@thundersoft.com") != NULL))
			{
				strcpy(buffer[index], data);
				field_index1++;
				index++;
				free(data);
				continue;
			}
			else
			{
				invalid_email++;
				if(invalid_email != 3)
				{
					printf("\nINFO: Please enter valid Email-id\n\n");
					free(data);
					continue;
				}
				else
				{
					printf("\nError: User enetered invalid Email-id three times, terminating the thread execution\n\n");
					fclose(file_pointer); //To close file
					pthread_mutex_unlock(&lock); //To release the lock acquired
					pthread_exit(NULL); //To terminate the thread execution
				}

			}
		}

		//To take user input for Employee id
		else if(strcasestr(buffer_field[field_index1], "id") != NULL)
		{
			int flag = 0, flag1 = 0, index1 = 0;

			//To check Employee-id is already present or not
			for(int i = 0;i < j;i++)
			{
				if(strcmp(data, buffer1_id[i]) == 0)
				{
					flag = 1;
					break;
				}
			}
			//Condition to check Employee id starts with '0'
			if(data[0] == '0' && data[1] == '2')
			{
				//To check employee id has only numbers
				while(data[index1] != '\0')
				{
					if(data[index1] >= 48 && data[index1] <= 57)
					{
						index1++;
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
				//To store user data to buffer
				if(flag1 == 0 && index1>6)
				{
					strcpy(buffer[index], data);
					index++;
					field_index1++;
					free(data);
					continue;
				}
				else
				{
					invalid_id++;
					if(invalid_id != 3)
					{
						printf("\nINFO: Please enter valid Employee-id\n\n");
						free(data);
						continue;
					}
					else
					{
						printf("\nError: User enetered invalid employee id three times, terminating the thread execution\n\n");
						fclose(file_pointer); //To close file
						pthread_mutex_unlock(&lock); //To release the lock acquired
						pthread_exit(NULL); //To terminate the thread execution
					}

				}
			}
			else
			{
				printf("\nINFO: Entered employee-id is already present\n\n");
				fclose(file_pointer); //To close file
				pthread_mutex_unlock(&lock); //To release the lock acquired
				pthread_exit(NULL); //To terminate the thread execution
			}
		}
		//To take user inputs for contact number
		else if(strcasestr(buffer_field[field_index1], "contact") != NULL)
		{
			int index1 = 0, flag = 0;
			//To check valid conditions for contact number
			if(data[0] >=54 && data[0] <= 57)
			{
				while(data[index1] != '\0')
				{
					if(data[index1] >= 48 && data[index1] <=57)
					{
						index1++;
					}
					else
					{
						flag = 1;
						break;
					}
				}
			}
			//To store user data to buffer
			if(flag == 0 && index1 == 10)
			{
				strcpy(buffer[index], data);
                                index++;
                                invalid_contact = 0;
                                field_index1++;
                                free(data);
                                continue;
                        }
                        else
                        {
                                invalid_contact++;
                                if(invalid_contact != 3)
                                {
                                        printf("\nError: Please enter valid contact number\n\n");
                                        free(data);
                                        continue;
                                }
                                else
                                {
                                        printf("\nError: User enetered invalid %s three times, terminating the thread execution\n\n", buffer_field[field_index1]);
                                        fclose(file_pointer); //To close file
                                        pthread_mutex_unlock(&lock); //To release the lock acquired
                                        pthread_exit(NULL); //To terminate the thread execution
                                }
			}
		}
		//To take user inputs for experience
		 else if(strcasestr(buffer_field[field_index1], "experience") != NULL)
		{
			int index1 = 0, flag = 0;
			//To check valid conditions for experience
                        if(data[0] >=48 && data[0] <= 57)
                        {
                                while(data[index1] != '\0')
                                {
                                        if(data[index1] >= 48 && data[index1] <=57)
                                        {
                                                index1++;
                                        }
                                        else
                                        {
                                                flag = 1;
                                                break;
                                        }
                                }
                        }
			//To store user data to buffer
                        if(flag == 0 && index1 == 2)
                        {
                                strcpy(buffer[index], data);
                                index++;
                                invalid_contact = 0;
                                field_index1++;
                                free(data);
                                continue;
                        }
                        else
                        {
                                invalid_exp++;
                                if(invalid_exp != 3)
                                {
                                        printf("\nError: Please enter valid experience in years\n\n");
					free(data);
                                        continue;
                                }
                                else
                                {
                                        printf("\nError: User enetered invalid %s three times, terminating the thread execution\n\n", buffer_field[field_index1]);
                                        fclose(file_pointer); //To close file
                                        pthread_mutex_unlock(&lock); //To release the lock acquired
                                        pthread_exit(NULL); //To terminate the thread execution
                                }
                        }
                }
		else
		{
			int index1 = 0, flag = 0, flag1 = 0;

			//To check string has no special characters other than space
			if((data[0] >= 65 && data[0] <= 90) || (data[0] >= 97 && data[0] <= 122))
			{
				while(data[index1] != '\0')
				{
					if(data[index1] == ' ' || (data[index1] >= 65 && data[index1] <= 90) || (data[index1] >= 97 && data[index1] <=122))
					{
						if(data[index1] == ' ')
						{
							if(flag1 == 0)
							{
								flag1 = 1;
								index1++;
							}
							else
							{
								flag = 1;
								break;
							}
						}
						else
						{
							index1++;
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
			//Condition to check whether buffer size is not more than MAX_LEN
			if(index1 >= MAX_LEN)
			{
				printf("\nError: Buffer exceeded\n\n");
				free(data);
				continue;
			}
			//To store user data to buffer
			if(flag == 0)
			{
				strcpy(buffer[index], data);
				index++;
				invalid_name = 0;
				field_index1++;
				free(data);
				continue;
			}
			else
			{
				invalid_name++;
				if(invalid_name != 3)
				{
					printf("\nError: No special characters allowed\n\n");
					free(data);
					continue;
				}
				else
				{
					printf("\nError: User enetered invalid %s three times, terminating the thread execution\n\n", buffer_field[field_index1]);
					fclose(file_pointer); //To close file
					pthread_mutex_unlock(&lock); //To release the lock acquired
					pthread_exit(NULL); //To terminate the thread execution
				}
			}
		}
	}
	//To store the employee details to excel sheet
	printf("\nInfo: Employee details entered successfully\n\n");
	for(int j = 0;j < index;j++)
	{
		fprintf(file_pointer, "%s\t", buffer[j]);
	}
	fprintf(file_pointer, "\n");
	fclose(file_pointer); //To close file
	pthread_mutex_unlock(&lock); //To release the acquired lock
}


void send_training_registration_form()
{
	//int form_option;
	int count = 0, index = 0, flag = 0;
	int form_option;
	struct dirent *directory_entry;
	char buffer_form[ROW_SIZE][COL_SIZE];
	DIR *dr = opendir(".");
	if(dr == NULL)
	{
		printf("\nError: Directory open not successfull\n\n");
	}
	while((directory_entry = readdir(dr)) != NULL)
	{
		if(strstr(directory_entry->d_name, "_training.xlsx") != NULL)
		{
			if(Forms_count == 0)
			{
				strcpy(Form[Forms_count], directory_entry->d_name);
				Forms_count++;
			}
			else
			{
				for(int i = 0;i < Forms_count;i++)
				{
					if(strcasecmp(Form[i], directory_entry->d_name) == 0)
					{
						flag = 1;
						break;
					}
				}
				if(flag == 0)
				{
					strcpy(Form[Forms_count], directory_entry->d_name);
					Forms_count++;
				}
			}

		}
	}
	closedir(dr);
	if(Forms_count > 0)
	{
		// To list all the trainings available
		printf("\nAvailable trainings registration forms are: \n");
		for(int i = 0;i < Forms_count;i++)
		{
			printf("%d. %s\n", i+1, Form[i]);
		}
		while(1)
		{
			char ch;
			printf("Enter the option to select particular training registration form: ");
			__fpurge(stdin);
			scanf("%d", &form_option);
			if(form_option > 0 && form_option <= Forms_count)
			{
				pthread_t thread;
				//Create threads and take different user inputs
				do
				{
					pthread_create(&thread, NULL, thread_handler_1, (void *)Form[form_option - 1]);
					pthread_join(thread, NULL); //To wait until particular thread termaination
					printf("Do you want to enter other employee details[y/n]? ");
					__fpurge(stdin);
					scanf("%c", &ch);
				}while(ch == 'y' || ch == 'Y');
				registration();
			}
			else
			{
				count++;
				if(count != 3)
				{
					printf("\nError: Invalid option\n\n");
				}
				else
				{
					printf("\nError: User entered invalid option for three times, returning to previous menu\n\n");
					registration();
				}
			}
		}
	}
	else
	{
		printf("Info: No training forms available\n");
		registration();
	}
}
