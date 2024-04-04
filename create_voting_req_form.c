#include"voting_request.h"
#include"create_voting_req_form.h"
#include<dirent.h>

//****************************Create voting form********************************

void create_voting_req_form(Vote **root)
{
	char form[COL_SIZE]; //Array of character to store name 
	char buffer_field[ROW_SIZE][COL_SIZE];
	int flag1 = 0, flag3 = 0, index = 0, invalid_form = 0, index1 = 0;
	FILE *file_pointer = NULL; 
	//To read the files in directory
	struct dirent *directory_entry; 
	DIR *dr = opendir("."); //To open the directory
	if(dr == NULL)
	{
		printf("\nError: Directory open not successfull\n\n");
	}
	//To store files into buffer
	while((directory_entry = readdir(dr)) != NULL)
	{
		if(strstr(directory_entry->d_name, "_voting.xlsx") != NULL)
		{
			if(Count_form == 0)
			{
				strcpy(Forms[Count_form], directory_entry->d_name);
				Count_form++;
			}
			else
			{
				for(int i = 0;i < Count_form;i++)
				{
					if(strcasecmp(Forms[i], directory_entry->d_name) == 0)
					{
						flag1 = 1;
						break;
					}
				}
				if(flag1 == 0)
				{
					strcpy(Forms[Count_form], directory_entry->d_name);
					Count_form++;
				}

			}

		}
	}
	closedir(dr);
        //To take user input for voting form names
	while(1)
	{
		int flag2 = 0, flag6 = 0;
		printf("Enter the voting form name: ");
		__fpurge(stdin); //To clear the input buffer
		scanf("%[^\n]%*c", form);
		//To check valid conditions for training name
		if((form[0] >= 65 && form[0] <= 90) || (form[0] >= 97 && form[0] <= 122))
		{
			while(form[index] != '\0')
			{
				if((form[index] >= 65 && form[index] <=90) || (form[index] >= 97 && form[index] <= 122) || (form[index] >= 48 && form[index] <= 57) || form[index] == '_')
				{
					if(form[index] == '_')
					{
						if(flag6 == 0)
						{
							flag6 = 1;
							index++;
						}
						else
						{
							flag2 = 1;
							break;
						}
					}
					else
					{
						index++;
						flag6 = 0;
					}
				}
				else
				{
					flag2 = 1;
					break;
				}
			}
		}
		else
		{
			flag2 = 1;
		}
		if(flag2 == 1)
		{
			invalid_form++;
			if(invalid_form != 3)
			{
				printf("\nInfo: Please enter valid voting form name\n\n");
				continue;
			}
			else
			{
				printf("\nError: User entered invalid option  three times, back to previous menu\n\n");
				voting_request(root);
			}
		}
		else
		{
			break;
		}
	}

	strcat(form, "_request.xlsx");

	//Loop to check whether the training name is already present or not
	for(int i = 0;i < Count_form; i++)
	{
		if(strcasecmp(Forms[i], form) == 0)
		{
			flag3 = 1;
		}
	}
	strcpy(Forms[Count_form], form); //Copy the content of form to Forms
	int invalid_count = 0;
	if(flag3 == 0)
	{ 
		while(1)
		{
			file_pointer = fopen(form, "w");// To open the file in write mode 
			if(file_pointer == NULL)
			{
				printf("File open not successfull\n");
			}
			int field_count; // variable to take user input for number of fields
			printf("Enter the number of fields required: ");
			__fpurge(stdin);
			scanf("%d", &field_count);
			int invalid_field = 0;
			if(field_count > 0 && field_count < 30)
			{
				Vote *lastnode = NULL;
				root[Count_form] = NULL;

				//To take user input for field name and store it to excel sheet
				for(int i = 0;i < field_count;i++)
				{
					//Allocating dynamic memory for each field 
					Vote *newnode = (Vote *)malloc(sizeof(Vote));
					while(1)
					{
						printf("Enter field name: ");
						__fpurge(stdin);
						scanf("%[^\n]%*c", newnode->fields);
						int index = 0, flag4 = 0, flag5 = 0;
						//To check valid conditions for field name
						if((newnode->fields[0] >= 65 && newnode->fields[0] <= 90) || (newnode->fields[0] >= 97 && newnode->fields[0] <= 122))
						{
							while(newnode->fields[index] != '\0')
							{
								if((newnode->fields[index] >= 65 && newnode->fields[index] <= 90) || (newnode->fields[index] >= 97 && newnode->fields[index] <= 122) || newnode->fields[index] == '_' || newnode->fields[index] == '-' || newnode->fields[index] == ' ')
								{
									if(newnode->fields[index] == '_' || newnode->fields[index] == '-' || newnode->fields[index] == ' ')
									{
										if(flag5 == 0)
										{
											flag5 = 1;
											index++;
										}
										else
										{
											flag4 = 1;
											break;
										}
									}
									else
									{
										index++;
										flag5 = 0;
									}
								}
								else
								{
									flag4 = 1;
									break;
								}
							}
						}
						else
						{
							flag4 = 1;
						}
						if(flag4 == 0)
						{
							int flag7 = 0;
							for(int i = 0;i < index1;i++)
							{
								if(strcasecmp(buffer_field[i], newnode->fields) == 0)
								{
									flag7 = 1;
									break;
								}
							}
							if(flag7 == 0)
							{
								newnode->link = NULL;
								fprintf(file_pointer, "%s\t", newnode->fields);//To store content of newnode->fields to file

								//To create linked list between each fields of one training regsitration form
								if(root[Count_form] == NULL)
								{
									root[Count_form] = newnode;
								}
								else
								{
									lastnode->link = newnode;
								}
								lastnode = newnode;
								strcpy(buffer_field[index1++], newnode->fields);
							
								invalid_field = 0;
							}
							else
							{
								printf("\n Entered field is already present\n\n");
								continue;
							}
							break;
						}
						else
						{
							invalid_field++;
							if(invalid_field != 3)
							{
								printf("\n Please enter valid field name\n\n");
								continue;
							}
							else
							{
								printf("\nError: User entered invalid field name three times, back to previous menu\n\n");
								remove(form);
								voting_request();
							}
						}
					}
				}
				fprintf(file_pointer, "\n");
				fclose(file_pointer); //To close the file
				Count_form++; //To increment Forms_count
				printf("\n INFO:%s created successfully\n\n",form);
				voting_request();
			}
			else
			{
				invalid_count++;
				if(invalid_count != 3)
				{
					printf("\n Invalid field count\n\n");
					continue;
				}
				else
				{
					printf("\nError: User entered invalid field count for three times, back to previous menu\n\n");
					remove(form);
					voting_request();
				}
			}

		}
	}
	else
	{
		printf("\n File is already present with given name\n\n");
		voting_request();
	}
}

