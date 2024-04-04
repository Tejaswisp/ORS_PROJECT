#include"feedback_module.h"
#include"feedback.h"

void feedback_module()
{
	int i = 0,j = 0,count = 0,option = 0,index = 0,training_form_count = 0;
	char c, form_names[ROW_LEN][COL_LEN];

	struct dirent *directory;  // Pointer for directory entry
	DIR *dir_ptr = opendir(".");     //opendir() returns a pointer of DIR type

	if (dir_ptr == NULL)  // opendir returns NULL if couldn't open directory
	{
		printf("Error:Could not open current directory" );
	}

	while ((directory = readdir(dir_ptr)) != NULL)       //to read the directory
	{
		if(strstr(directory->d_name,"_training.xlsx"))   //checking for _training.xlsx files in pwd
		{
			strcpy(form_names[index],directory->d_name);
			index++;
		}
	}
	closedir(dir_ptr);  //closing the directory

	while(index > 0)
	{
		int line_count = 0, k = 0;
		char buffer1[COL_LEN],buffer2[COL_LEN];
		FILE *fp=fopen(form_names[j],"r");         //opening the _tarining.xlsx in read mode
		if(fp==NULL)
		{
			printf("Error:Cannot open file\n");
		}

		for (c = getc(fp); c != EOF; c = getc(fp))     //counting the number of lines in that conducted training sheet
		{
			if (c == '\n') // Increment count if this character is newline
				line_count = line_count + 1;
		}


		if(line_count > 1) //checking the conducted training xl file,checking if only form is created with no field enetred by the user
		{
			while(form_names[j][k] != '.')   //copy only the training form name leaving the file extension _training.xlsx
			{
				buffer2[k] = form_names[j][k];
				k++;
			}
			buffer2[k]='\0';
			strcpy(Training_form_name[training_form_count],buffer2); //copying conducted training form name 
			training_form_count++;
		}

		j++;
		index--;
		fclose(fp);    //closing the file
	}

	if(training_form_count > 0)  //feedback_form_count holds the total number of conducted trainings 
	{
		printf("Available training forms:\n");
		for(i=0;i<training_form_count;i++) //to print the available registration forms
		{
			printf("%d.%s\n",i+1,Training_form_name[i]);
		}
		while(1)
		{
			printf("Please select the option from the avilable training forms:");
			__fpurge(stdin);      
			scanf("%d",&option);

			if(((option > training_form_count) || (option <= 0)) && (count != 2))  
			{
				printf("Invalid option\n\n");
				count++;
			}
			else
			{
				if(option <= training_form_count && option != 0)
				{
					feedback(option);     //calling the feedback function to take feedback from user
				}
				else
				{
					printf("User Entered 3 times wrong option,returning to previous menu\n\n");
					training();                            //if user enter 3 times wrong option back to main menu
				}
			}
		}
	}
	else
	{
		printf("No trainings happened,to give feedback\n");
		training();
	}
}
