#include <stdio.h>
int main(void)
{
	int i;

	printf("Printing Even Numbers From 0 to 100: \n");

	for (i = 0; i <= 100; i++)
	{
		// condition for a nuber to be even number => division of number by 2 leaves no remainder (remainder = 0)
		// if remainder is not 0, the number is odd number...
		if (i % 2 != 0) 
		{
			continue;
		}
		else
		{
			printf("\t%d\n", i);
		}
	}

	return 0;
}
