#include<stdio.h>
int main(void)
{
	int i;
	char ch;

	printf("Printing Even Numbers From 1 to 100 For Every User Input. Exitting the Loop When User Enters Character 'Q' or 'q' : \n\n");
	printf("Enter Character 'Q' or 'q' To Exit Loop : \n\n");

	for (i = 1; i <= 100; i++)
	{
		printf("\t%d\n", i);
		ch = getchar();
		if (ch == 'Q' || ch == 'q')
		{
			break;
		}
	}
	

	return 0;
}
