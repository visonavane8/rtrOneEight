#include <stdio.h>
int main(void)
{
	int i, j, k;

	i = 1;
	do
	{
		printf("i = %d\n", i);
		printf("--------\n\n");
		
		j = 1;
		do
		{
			printf("\tj = %d\n", j);
			printf("\t--------\n\n");
			
			k = 1;
			do
			{
				printf("\t\tk = %d\n", k);
				k++;
			}while (k <= 3);
			printf("\n\n");
			j++;
		}while (j <= 5);
		printf("\n\n");
		i++;
	}while (i <= 10);
	
	return 0;
}
