#include"registration.h"
#include"create_registration_form.h"
#include"delete_registration_form.h"
#include"send_registration_form.h"

//*******************************************Training resgistration*****************************************

void registration()
{
	int choice;

	static Employee_training_data *first_field[COL_SIZE]; //An array of pointer to store the address of first field in each training registration form
	int count_option = 0;
	//Array of Function pointers to call functions
	//void (*fp[3])(Employee_training_data **) = {create_training_registration_form, delete_training_registration_form, send_training_registration_form};
	while(1)
	{
		printf("1. Create Training Registration form\n2. Delete Training Registration form\n3. Send Training Registration form\n4. Main menu");
		printf("\nEnter the option: ");
		__fpurge(stdin);
		scanf("%d", &choice);
		//To call functions based on user choice
		switch(choice)
		{
			case 1: create_training_registration_form(first_field);
				break;
			case 2: delete_training_registration_form(first_field);
				break;
			case 3: send_training_registration_form();
				break;
			case 4: main();
				break;
			default:  count_option++;
				  if(count_option == 3)
				  {
					  printf("\nError: User entered invalid option for three times, returning to previous menu\n\n");
					  training();
				  }
				  else
				  {
					  printf("\nError: Invalid option\n\n");
				  }
				  break; 
		}
	}
}
