#include <stdio.h>
int main(void)
{
	int i, j;

	i = 1;
	while(i <= 10)
	{
		printf("i = %d\n", i);
		printf("--------\n\n");
		
		j = 1;
		while (j <= 5)
		{
			printf("\tj = %d\n", j);
			j++;
		}
		i++;
		printf("\n\n");
	}
	return 0;
}
