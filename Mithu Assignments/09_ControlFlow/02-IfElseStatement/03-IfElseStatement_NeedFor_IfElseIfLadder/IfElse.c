#include<stdio.h>
int main(void)
{
	int num;

	printf("Enter value for num:");
	scanf("%d", &num);

	if(num < 0)
	{
		printf("num = %d is less than 0 \n",num);
	}
	else
	{
		if((num>0) && (num<=100))
		{
			printf("num = %d is between 0 and 100 \n",num);
		}
		else
		{
			if((num>100) && (num<=200))
			{
				printf("num = %d is between 100 and 200 \n", num);
			}
			else
			{
				if((num>200) && (num<=300))
				{
					printf("num = %d is between 200 and 300 \n", num);
				}
				else 
				{
					if((num>300) && (num<=400))
					{
						printf("num = %d is between 300 and 400 \n", num);
					}
					else
					{
						if((num>400) && (num<=500))
						{
							printf("num = %d is between 400 and 500 \n", num);
						}
						else 
						{
							printf("num = %d is greater than 500 \n", num);
						}

					}

				} 

			} 

		}

	} 

	return 0;
}
