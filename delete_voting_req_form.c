#include"voting_request.h"
#include"delete_voting_req_form.h"
#include<dirent.h>

//****************************Delete voting form********************************

void delete_voting_req_form(Vote **root)
{
	int form_option; // variable to select one training from available trainings
	int count_option = 0;
	char form_name[COL_SIZE];

	int count = 0, index = 0, flag = 0;
	//To read the files in directory and store files to buffer
        struct dirent *directory_entry;
        char buffer_form[ROW_SIZE][COL_SIZE];
        DIR *dr = opendir(".");
        if(dr == NULL)
        {
                printf("\nError: Directory open not successfull\n\n");
        }
        while((directory_entry = readdir(dr)) != NULL)
        {
                if(strstr(directory_entry->d_name, "_request.xlsx") != NULL)
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
                                                flag = 1;
                                                break;
						}
                                }
                                if(flag == 0)
                                {
                                                strcpy(Forms[Count_form], directory_entry->d_name);
                                                Count_form++;
                                }
                        }

                }
        }
        closedir(dr);

	//To display  available voting form
	if(Count_form > 0)
	{
		printf("\nAvailable voting form are: \n");
		for(int i = 0;i < Count_form;i++)
		{
			printf("%d. %s\n", i+1, Forms[i]);
		}
		int delete_count = 0;
		//To take user input for user option to select voting  form
		while(1)
		{
			printf("Enter the option to delete voting form: ");
			__fpurge(stdin);
			scanf("%d", &form_option);
			if(form_option > 0 && form_option <= Count_form)//To check condition for invalid option
			{
				strcpy(form_name,Forms[form_option-1]);

				//To delete the file selected from the user
				while(1)
				{
					char ch[5];
					printf("\nAre you sure, you want to delete the file?(Yes/No) ");
					__fpurge(stdin);
					scanf("%[^\n]%*c",ch);
					if(strcasecmp(ch, "Yes") == 0)
					{
						if(remove(form_name)==0)
						{
							printf("\nInfo: File deleted successfully\n\n");
							for(int i = form_option;i < Count_form;i++)
							{
								strcpy(Forms[i-1], Forms[i]);
								root[i-1] = root[i];

							}
							Count_form--; //To decrement forms count
							voting_request();
						}
						else
						{
							printf("\n File is not deleted\n\n");
							voting_request();
						}
					}
					else if(strcasecmp(ch, "No") == 0)
					{
						printf("\n File is not deleted\n\n");
						voting_request();
					}
					else
					{
						delete_count++;
						if(delete_count != 3)
						{
							printf("\n Invalid option\n");
							continue;
						}
						else
						{
							printf("\nError: User entered invalid option for three times, back to previous menu\n\n");
							voting_request();
						}
					}
				}
			}
			else
			{
				count_option++;
				if(count_option != 3) //To check condition for invalid option for three times
				{
					printf("\nError: Invalid option\n\n");

				}
				else
				{
					printf("\nError: User entered invalid option for three times\n\n");
					voting_request();
				}
			}
		}
	}
	else
	{
		printf("\nError: No voting forms available\n\n");
		voting_request();
	}
}



