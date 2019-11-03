#include <stdio.h>
int main(void)
{
	int i;

	printf("Printing Digits 10 to 1 : \n\n");

	i = 10;
	while (i >= 1)
	{
		printf("\t%d\n", i);
		i--;
	}

	return 0;
}
