#include"registration.h"
#include"delete_registration_form.h"

//****************************Delete training registration form********************************

void delete_training_registration_form(Employee_training_data **first_field)
{
	int form_option; //Integer variable to select one training from available trainings
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

	//To display trainings available
	if(Forms_count > 0)
	{
		printf("\nAvailable trainings registration form are: \n");
		for(int i = 0;i < Forms_count;i++)
		{
			printf("%d. %s\n", i+1, Form[i]);
		}
		int delete_count = 0;
		//To take user input for user option to select training registration form
		while(1)
		{
			printf("Enter the option to delete training registration form: ");
			__fpurge(stdin);
			scanf("%d", &form_option);
			if(form_option > 0 && form_option <= Forms_count)//To check condition for invalid option
			{
				strcpy(form_name,Form[form_option-1]);

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
							for(int i = form_option;i < Forms_count;i++)
							{
								strcpy(Form[i-1], Form[i]);
								first_field[i-1] = first_field[i];

							}
							Forms_count--; //To decrement forms count
							registration();
						}
						else
						{
							printf("\nInfo: File is not deleted\n\n");
							registration();
						}
					}
					else if(strcasecmp(ch, "No") == 0)
					{
						printf("\nInfo: File is not deleted\n\n");
						registration();
					}
					else
					{
						delete_count++;
						if(delete_count != 3)
						{
							printf("\nInfo: Invalid option\n");
							continue;
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
				count_option++;
				if(count_option != 3) //To check condition for invalid option for three times
				{
					printf("\nError: Invalid option\n\n");

				}
				else
				{
					printf("\nError: User entered invalid option for three times\n\n");
					registration();
				}
			}
		}
	}
	else
	{
		printf("\nError: No training registration forms available\n\n");
		registration();
	}
}
