
/************************Main module implementation********************/
#include"main.h" //headerfile inclusion
#include<ctype.h>

void main()
{

	int count=0;			//local variable for invalid option counting

	int option;			// local variable for option choosing from menu

	printf(" Main menu \n");

	printf(" 1.Training \n 2.Voting \n 3.Exit\n");


	void (*fp[3])()={training,voting,exit}; //Array of function pointers 

	while(1)
	{

		printf("Enter the option\n");
		__fpurge(stdin);

		scanf("%d",&option);
		if((option >0) && (option<=9))		//checking for the given input is digit or not
		{
			switch(option)
			{
				case 1: fp[option-1]();break; //function call for training
				case 2: fp[option-1]();break; //function call for votiong
				case 3: printf("Exiting from Application\n");exit(0);		  //terminating the application
				default:count++;
				if(count== 3)
				  {
					  printf("\nError: User entered invalid option for 3times\nExiting from Application\n");
					  exit(0);
		
				  }
				  else
				  {
					  printf("\nError: Invalid option\n");
				  } 
				  break;    	//counting the invalid options 
			}
		}
		else{
		count++;
		if(count<3)
		{
		printf("Error: Invalid option\n");
		}
		else{
		printf("\nError: User entered invalid option for 3times\nExiting from Application\n");
		exit(0);
		}
		}
	}
			



}

/**************************************Creating Training Menu**************************/
void training()
{
	int option_t;			// local variable for option choosing from menu	

	int option_count=0;		//local variable for invalid option counting

	printf(" Training Menu\n");

	printf(" 1.Registration\n 2.Feedback\n 3.Main menu\n");

	void (*fp_t[3])()={registration,feedback_module};//feedback}; //Array of function pointers 

while(1)
{
	printf("Enter the option\n");
	__fpurge(stdin);
	scanf("%d",&option_t);
	if((option_t >= 0)&&(option_t <= 9))	//checking for the given input is digit or not
	{

		switch(option_t)
		{
			case 1: fp_t[option_t-1]();break; // function call for training_module
			case 2: fp_t[option_t-1]();break;   // function call for feedback
			case 3: main();			// going backto main menu
			default:option_count++;
				if(option_count== 3)
				  {
					  printf("\nError: User entered invalid option for three times\n\n");
					  main();
		
				  }
				  else
				  {
					  printf("\nError: Invalid option\n");
				  } 
				  break;
		}
		
	}
	else{
		option_count++;
		if(option_count<3)
		printf("\nError: Invalid option\n");
		else{
		printf("\nError: Invalid option 3 times Going back to Main menu\n\n");
		main();
		}
		}  	
}
}

/**************************Voting menu creation****************************/
void voting()
{
	int option_v;			// local variable for option choosing from menu	

	int option_vcount=0;		//local variable for invalid option counting

	printf("Voting Menu\n");

	printf(" 1.Voting request \n 2.Voting response \n 3.Main menu\n");

	void (*fp_v[3])()={voting_request,voting_response,main}; //Array of function pointers 

while(1)
{
	printf("Enter the option\n");
	__fpurge(stdin);
	scanf("%d",&option_v);
	if((option_v >= 0)&&(option_v <= 9))	//checking for the given input is digit or not
	{

		switch(option_v)
		{
			case 1: fp_v[option_v -1]();break; // function call for training_module
			case 2: fp_v[option_v -1]();break;   // function call for feedback
			case 3: main();			// going backto main menu
			default:option_vcount++;
				if(option_vcount== 3)
				  {
					  printf("\nError: Invalid option 3 times Going back to Main menu\n\n");
					  main();
		
				  }
				  else
				  {
					  printf("\nError: Invalid option\n");
				  } 
				  break;
		}
		
	}
	else{
		option_vcount++;
		if(option_vcount<3)
		printf("\nError: Invalid option\n");
		else{
		printf("\nError:Invalid option 3 times Going back to Main menu\n\n");
		main();
		}
		}  	
}
}
