#include<stdio.h>
int main(void)
{
	int num_month;

	printf("Enter Number Of Month (1 to 12) :");
	scanf("%d",&num_month);

	if(num_month == 1) 
		printf("Month Number %d is January \n",num_month);

	else if(num_month == 2) 
		printf("Month Number %d is February \n",num_month);

	else if(num_month == 3) 
		printf("Month Number %d is March \n",num_month);

	else if(num_month == 4)
		printf("Month Number %d is April \n",num_month);

	else if(num_month == 5)
		printf("Month Number %d is May \n",num_month);

	else if(num_month == 6) 
		printf("Month Number %d is June \n",num_month);

	else if(num_month == 7) 
		printf("Month Number %d is July \n",num_month);

	else if(num_month == 8) 
		printf("Month Number %d is August \n",num_month);

	else if(num_month == 9) 
		printf("Month Number %d is September \n",num_month);

	else if(num_month == 10)
		printf("Month Number %d is October \n",num_month);

	else if(num_month == 11) 
		printf("Month Number %d is November \n",num_month);

	else if(num_month == 12) 
		printf("Month Number %d is December \n",num_month);

	else
		printf("Invalid Month Number %d Entered Please try again...\n",num_month);

	printf("If else if ladder complete \n");

	return 0;
}
