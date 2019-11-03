#include<stdio.h>
int main(void)
{
	int a, b;
	int result;

	char option, option_division;

	printf("Enter Value For 'A' : ");
	scanf("%d", &a);

	printf("Enter Value For 'B' : ");
	scanf("%d", &b);

	printf("Enter Option In Character : \n\n");
	printf("'A' or 'a' For Addition : \n");
	printf("'S' or 's' For Subtraction : \n");
	printf("'M' or 'm' For Multiplication : \n");
	printf("'D' or 'd' For Division : \n\n");

	printf("Enter Option : ");
	option = getchar();
	option = getchar();

	if (option == 'A' || option == 'a')
	{
		result = a + b;
		printf("Addition Of A = %d And B = %d Gives Result %d \n", a, b, result);
	}

	else if (option == 'S' || option == 's')
	{
		if (a >= b)
		{
			result = a - b;
			printf("Subtraction Of B = %d From A = %d Gives Result %d \n", b, a, result);
		}
		else
		{
			result = b - a;
			printf("Subtraction Of A = %d From B = %d Gives Result %d \n", a, b, result);
		}
	}

	else if(option == 'M' || option == 'm')
	{
		result = a * b;
		printf("Multiplication Of A = %d And B = %d Gives Result %d \n", a, b, result);
	}
	
	else if (option == 'D' || option == 'd')
	{
		printf("Enter Option In Character : \n\n");
		printf("'Q' or 'q' or '/' For Quotient Upon Division : \n");
		printf("'R' or 'r' or '%%' For Remainder Upon Division : \n");

		printf("Enter Option : ");
		option_division = getchar();
		option_division = getchar();
		
		if (option_division == 'Q' || option_division == 'q' || option_division == '/')
		{
			if (a >= b)
			{
				result = a / b;
				printf("Division Of A = %d By B = %d Gives Quotient = %d \n", a, b, result);
			}
			else
			{
				result = b / a;
				printf("Division Of B = %d By A = %d Gives Quotient = %d \n", b, a, result);
			}
		}

		else if (option_division == 'R' || option_division == 'r' || option_division == '%')
		{
			if (a >= b)
			{
				result = a % b;
				printf("Division Of A = %d By B = %d Gives Remainder = %d \n", a, b, result);
			}
			else
			{
				result = b / a;
				printf("Division Of B = %d By A = %d Gives Remainder = %d \n", b, a, result);
			}
		}
		
		else
			printf("Invalid Character %c Entered For Division \n", option_division);
	}

	else
		printf("Invalid Character %c Entered\n",option);

	printf("If Else If ladder complete\n");

	return 0 ;
}
