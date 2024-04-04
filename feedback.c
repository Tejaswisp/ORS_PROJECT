#include"feedback.h"
#include"feedback_module.h"

pthread_mutex_t lock;   //declaring mutex variable

int employee_id(char* user_buffer_empid,int *option); //employee_id function declaration
int employee_name(char *user_buffer_name);   //employee_name function declaration
int employee_email(char *user_buffer_email);  //employee_email function declation
int employee_reporting_mgr(char *user_buffer_reporting_mgr);   //employee_rporting_mgr function declaration
int employee_feedback(char *user_buffer_feedback);        //employee_feedback function declaration


void *feedback_thread(void *t1)        //thread definition
{
	pthread_mutex_lock(&lock); //to acquire the lock
	char form[COL_LEN];  //char array to store one feedback form name
	char user_buffer1[MAX_SIZE],user_buffer2[MAX_SIZE],user_buffer3[MAX_SIZE],user_buffer4[MAX_SIZE],user_buffer5[MAX_SIZE];  //buffer to copy the user inputted emp_id,emp_name,emp_emai,reporting_mgr,feedback from the user
	int *option = (int *)t1; 
	int return_value_id = 0, return_value_name = 0,return_value_email = 0,return_value_reporting_mgr = 0,return_value_feedback = 0;

	return_value_id=employee_id(user_buffer1,option);
	if(return_value_id==1)        //checking if the user is not registered for the training
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	return_value_name=employee_name(user_buffer2);   //calling employee_name function to take emp_name from the user
	if(return_value_name==1)        //checking if the user has entered three times Invalid emp_name
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	return_value_email=employee_email(user_buffer3);  //calling emloyee_email function to take emp_email fromthe user
	if(return_value_email==1)        //checking if the user has enetered three times Invalid email_id
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	return_value_reporting_mgr=employee_reporting_mgr(user_buffer4);   //calling the employee_reporting_mgr function to take retporting manager name
	if(return_value_reporting_mgr==1)        //checking if the user haa enetered three times Invalid reporting_mgr name
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	return_value_feedback=employee_feedback(user_buffer5);   //calling the employee_feedback function to take feedback from the user		
	if(return_value_feedback==1)        //checking if the user has used special characters while giving feedback for three times
	{
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}

	strcpy(form, Training_form_name[*option - 1]);   //copying the training name to form
	strcat(form, "_feedback.xlsx");     //concatenating the _training.xlsx into form1
	FILE *fp2 = fopen(form, "a");            //opening the feedback xl sheet in append mode
	if(fp2==NULL)           //checking if the file is opened or not
	{
		printf("Error:Cannot open file\n");
	}
	fprintf(fp2,"%s\t%s\t%s\t%s\t%s\n",user_buffer1,user_buffer2,user_buffer3,user_buffer4,user_buffer5); //storing user details into feedback xl sheet
	fclose(fp2); //to close the file
	printf("Your response has been recorded\n\n");
	pthread_mutex_unlock(&lock);     //to release the lock
}


void feedback(int option)
{
	char form_name[COL_LEN]; //An arraay of characters to store the one training feedback form name
	char c,choice;  //to store the character    
	int line_count = 0,flag = 0;

	strcpy(form_name,Training_form_name[option-1]);   //copying conducted training form name
	
	strcat(form_name,"_feedback.xlsx");

	struct dirent *directory_entry;  //Pointer for directory entry
	DIR *dr = opendir(".");    //opendir() returns a pointer of DIR type
	if(dr == NULL)
	{
		printf("\nError: Directory open not successfull\n\n");
	}
	while((directory_entry = readdir(dr)) != NULL)   //reading the pwd
	{
		if(strcasecmp(form_name,directory_entry->d_name) == 0)    //checking if the feedback xl sheet is already present or not
		{
			flag = 1;
			break;

		}
	}
	closedir(dr);    //closing the directory

	if(flag == 0)
	{
		
		FILE *fp=fopen(form_name,"w");     //opening the _feedback.xlsx file in write mode
		if(fp==NULL)    //checking if file exists or not
		{
			printf("Error:Cannot open the file\n\n");
		}
		else
		{
			Employee_training_feedback user={"emp_id","emp_name","emp_email","reporting_mgr","feedback"}; //initializing the field names using the structure varible
			fprintf(fp,"%s\t%s\t%s\t%s\t%s\n",user.emp_id,user.emp_name,user.emp_email,user.reporting_mgr,user.feedback); //printing the field names into _feedback.xlsx file
			fclose(fp); //closing the file
		}
	}
	pthread_t thread[1];  //creating thread to take three i/p from user
	do
	{
		pthread_create(&thread[0], NULL, feedback_thread, (void *)&option); //to take user1 i/p
		pthread_join(thread[0], NULL); //wait for the thread to complete
		printf("Do you want to continue with other employee details[y or n]:");
		__fpurge(stdin);
		scanf("%c",&choice);
	}while(choice == 'y' || choice == 'Y');
	training();
}



int employee_id(char* user_buffer_empid,int *option)
{

	char form[COL_LEN]; //char array to store one training form name
	char form1[COL_LEN];  //char array to store one feedback form name
	char emp_id[COL_LEN];     //char array to store user inputted emp_id to takefeedback
	char buffer1[MAX_SIZE][MAX_SIZE];  //buffer to store all the fields in the training xl file
	char buffer2[MAX_SIZE][MAX_SIZE];  //buffer to store only the emp_id fron that traing xl file
	char buffer3[MAX_SIZE][MAX_SIZE];  //buffer to store all the fields in the feedback xl sheet
	char buffer4[MAX_SIZE][MAX_SIZE];   //buffer to store the only the emp_id's present in the feedback xl sheet
	strcpy(form, Training_form_name[*option - 1]);  //copying name of the training name to form
	strcat(form, ".xlsx");   //concatenating _training.xlsx into form
	FILE *file_pointer = fopen(form, "r");   //opening the file in read mode
	int i = 0,j = 0,m = 0,flag = 0;

	printf("Enter the Emp_id:");      //taking the emp_id from user
	__fpurge(stdin);                 //clear the buffer
	scanf("%s",emp_id);

	if(emp_id[0] == '0' && emp_id[1] == '2')     //checking the first and second digits in emp_id    
	{
		while(emp_id[m] != '\0')          //checking the for the valid emp_id
		{
			if((emp_id[m] >= 47) &&  (emp_id[m] <= 58))
			{
				m++;
			}
			else
			{
				printf("Invalid emp-id\n\n");
				return 1;
			}
		}
	}
	else
	{
		printf("Invalid emp-id\n\n");
		return 1;
	}

	while(!feof(file_pointer))    //Reading whole conducted training xl file 
	{
		fscanf(file_pointer,"%s\t",buffer1[i]);
		if(buffer1[i][0]== '0')   //checking for emp_id 
		{
			strcpy(buffer2[j],buffer1[i]);    //storing that emp_id into another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer);
	for(int x=0;x<j;x++)
	{
		if(strcmp(emp_id,buffer2[x]) == 0)   //to comapare the user enetred emp_id with the training registered emp_id's
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		printf("This user has not registered for the training\n\n");
		return 1;
	}
	else
	{
		int k=0,l=0,flag1=0;
		strcpy(form1, Training_form_name[*option - 1]);  //copying name of the training name to form1
		strcat(form1, "_feedback.xlsx");   //concatenating _training_feedback.xlsx into form1
		FILE *file_pointer1 = fopen(form1, "r");   //opening the file in read mode
		while(!feof(file_pointer1))    //Reading whole conducted feedback xl file 
		{
			fscanf(file_pointer1,"%s\n",buffer3[k]);
			if(buffer3[k][0]== '0')   //checking for emp_id 
			{
				strcpy(buffer4[l],buffer3[k]);    //storing that emp_id into another buffer
				l++;
			}
			k++;
		}

		fclose(file_pointer1);
		for(int z=0;z<l;z++)
		{
			if(strcmp(emp_id,buffer4[z]) == 0)  //checking if the user has already given the feedback
			{
				flag1=1;
				break;
			}
		}
		if(flag1==1)
		{
			printf("This user has already given the feedback\n\n");
			return 1;
		}
		else
		{

			strcpy(user_buffer_empid, emp_id);             //storing the emp_id into buffer
		}

	}
}



int employee_name(char* user_buffer_name)   //function definition to take emp_name from user
{
	char name[FIELD_LEN];
	int buffer_size = 0, k = 0, flag = 0;
	static int count = 0;
	printf("Enter the emp_name:"); 
	__fpurge(stdin);            //to clear the buffer
	scanf("%[^\n]%*c",name);      //to take emp_name from the user

	if((name[k] >= 65 && name[k] <= 90) || (name[k] >= 97 && name[k] <= 122))
	{
		while(name[k] != '\0')
		{
			buffer_size++;
			if(buffer_size > FIELD_LEN)    //checking for the max characters to take for the name
			{
				printf("Buffer size is exceeded\n\n");
				employee_name(user_buffer_name);    //if size exceeds calling the function to again take the emp_name
			}
			if(name[k] == ' ' || (name[k] >= 65 && name[k] <= 90) || (name[k] >= 97 && name[k] <=122)) //checking the user emp_name contains only space and alphabets 
			{
				if(name[k] == ' ' && name[k+1] == ' ') //checking for extra spaces
				{
					flag = 1;
					break;
				}
				k++;
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
	if(flag == 0)
	{
		strcpy(user_buffer_name,name); //copying the user inputted emp_name to buffer
	}
	else
	{
		if(count != 2)          //checking if the user has entered invalid name more than 2 times
		{
			count++;
			printf("Invalid name\n\n");
			employee_name(user_buffer_name);  //calling the function again to enter the valid emp_name
		}
		else
		{
			printf("You entered three times Invalid name\n\n");
			count = 0;
			return 1;
		}
	}
}


int employee_email(char* user_buffer_email)
{
	char Email_id[MAX_SIZE];
	int i = 0,flag = 0;
	static int count = 0;

	printf("Enter the email_id:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",Email_id);      // to take the email_id from the user

	if(Email_id[0]>=97 && Email_id[0]<=122)  //checking if the first character in the email-id is lowercase letter or not
	{
		while(Email_id[i] != '@')     //cheking if the email-id before @ conatains only alphabets and '.'
		{
			if((Email_id[i]>=97 && Email_id[i]<=122) || (Email_id[i]>=65 && Email_id[i]<=90) || Email_id[i] == '.')
			{ 
				i++;
			}
			else
			{
				flag = 1;
				break;
			}
		}

		if(flag == 0)
		{
			if(strstr(Email_id, "@thundersoft.com") )  //checking for @thundersoft.com in that user entered emeil id
			{
				strcpy(user_buffer_email, Email_id);
			}
			else
			{
				flag = 1;
			}
		}
	}
	else
	{
		flag = 1;
	}
	if(flag == 1)
	{
		if(count != 2) //checking if the user has entered Invalid email-id more than 2 times
		{
			count++;
			printf("Invalid email_id\n\n");
			employee_email(user_buffer_email);  //calling the function again to enter the valid emp_email
		}
		else
		{
			printf("You entered three times Invalid email_id\n\n");
			count = 0;
			return 1;
		}
	}
}


int employee_reporting_mgr(char* user_buffer_reporting_mgr)
{
	char reporting_manager[FIELD_LEN];
	printf("Enter the Reporting manager name:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",reporting_manager);          //to take reporting manager name from the user
	int  k = 0, flag = 0,buffer_size = 0;
	static int count = 0;

	if((reporting_manager[k] >= 65 && reporting_manager[k] <= 90) || (reporting_manager[k] >= 97 && reporting_manager[k] <=122))
	{
		while(reporting_manager[k] != '\0') 
		{
			buffer_size++;
			if(buffer_size > FIELD_LEN) //checking the max charcaters that that entered by the user
			{
				printf("Buffer size is exceeded\n\n"); 
				employee_reporting_mgr(user_buffer_reporting_mgr); //calling the function again to take valid reporting manager anme
			} //checking for the ' ' capital and small lettres 
			if(reporting_manager[k] == ' ' || (reporting_manager[k] >= 65 && reporting_manager[k] <= 90) || (reporting_manager[k] >= 97 && reporting_manager[k] <=122))
			{ 
				if(reporting_manager[k] == ' ' && reporting_manager[k+1] == ' ') //checking for extra spaces
				{
					flag = 1;
					break;
				}
				k++;
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
	if(flag == 0)
	{
		strcpy(user_buffer_reporting_mgr,reporting_manager); //copying the user inputted reporting manager name to buffer
	}
	else
	{
		if(count != 2)  //checking if the user has entered invalid reporting-manager name more than 2 times
		{
			count++;
			printf("Invalid reporting manager name\n\n");
			employee_reporting_mgr(user_buffer_reporting_mgr);    //calling the function again to enter the valid reporting manager name
		}
		else
		{
			printf("You entered three times Invalid Reporting manager name\n\n");
			count = 0;
			return 1;
		}
	}
}


int employee_feedback(char *user_buffer_feedback)
{
	char feedback_training[MAX_SIZE];

	printf("Enter the Feedback for the training:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",feedback_training);   //to take feedback from the user
	int feedback_count=0,k = 0, flag = 0;
	static int count = 0;

	if((feedback_training[k] >= 65 && feedback_training[k] <= 90) || (feedback_training[k] >= 97 && feedback_training[k] <=122))
	{
		while(feedback_training[k] != '\0')
		{
			if(feedback_count > MAX_SIZE) //checking max characeters that can be entered by the user for giving feedback
			{
				printf("Buffer Size is exceeded\n");
				employee_feedback(user_buffer_feedback);
			} 
			//checking for space and alphabets
			if(feedback_training[k] == ' ' || (feedback_training[k] >= 65 && feedback_training[k] <= 90) || (feedback_training[k] >= 97 && feedback_training[k] <=122))
			{
				if(feedback_training[k] == ' ' && feedback_training[k+1] == ' ') //checking for extra spaces
				{
					flag = 1;
					break;
				}
				k++;
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
	if(flag == 0)
	{
		strcpy(user_buffer_feedback,feedback_training);   //copying the user inputted feedback into buffer
	}
	else
	{
		if(count != 2)    //checking if the user has entered special characters while giving feedback more than 2 times
		{
			count++;
			printf("Invalid feedback\n\n");
			employee_feedback(user_buffer_feedback);  //calling the function again to enter the valid feedback(i.e no special characters are allowed)
		}
		else
		{
			printf("You entered Invalid feedback for three times \n\n");
			count = 0;
			return 1;
		}
	}
}
