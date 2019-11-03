#include<stdio.h>
int main(void)
{
	int num_month;

	printf("Enter number of month (1 to 12) :");
	scanf("%d",&num_month);

	switch(num_month)
	{
	case 1: 
		printf("Month Number %d Is January \n",num_month);
		break;

	case 2: 
		printf("Month Number %d Is February \n",num_month);
		break;

	case 3: 
		printf("Month Number %d Is March \n",num_month);
		break;

	case 4: 
		printf("Month Number %d Is April \n",num_month);
		break;

	case 5: 
		printf("Month Number %d Is May \n",num_month);
		break;

	case 6: 
		printf("Month Number %d Is June \n",num_month);
		break;

	case 7: 
		printf("Month Number %d Is July \n",num_month);
		break;

	case 8:
		printf("Month Number %d Is August \n",num_month);
		break;

	case 9:
		printf("Month Number %d Is September \n",num_month);
		break;

	case 10: 
		printf("Month Number %d Is October \n",num_month);
		break;

	case 11: 
		printf("Month Number %d Is November \n",num_month);
		break;

	case 12:
		printf("Month Number %d Is December \n",num_month);
		break;

	default:
		printf("Invalid Month Number %d Entered\n",num_month);
		break;
	}

	printf("Switch case complete \n");

	return 0;
}
