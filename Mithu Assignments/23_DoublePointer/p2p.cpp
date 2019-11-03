#include<stdio.h>
#include<stdlib.h>
int main()
{
	int **Vinit_ptr = NULL;
	Vinit_ptr = (int**)malloc(5 * sizeof(int*));

	if (Vinit_ptr == NULL)
	{
		printf("Memory Allocation Failed \n");
		exit(0);
	}

	for (int i = 0; i < 5; i++)
	{
		Vinit_ptr[i] = (int*)malloc(3 * sizeof(int));

		if (Vinit_ptr[i] == NULL)
		{
			printf("Memory Allocation Failed exit now");
			exit(0);
		}
	}
	//Getting Elements
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("\nEnter For Vinit_ptr[%d][%d] : \n", i, j);
			scanf("%d", &Vinit_ptr[i][j]);
			printf("\n");
		}
	}

	//Printing Elements

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%5d", Vinit_ptr[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	

	//Address of *Vinit_ptr
	printf("Address of *Vinit_ptr ");
	printf("\n\n");
	for (int i = 0; i < 5; i++)
	{
			printf(" %p ", Vinit_ptr[i]);
			printf("\n\n");
	}	

	printf("Checking Address Do They Match with Them");
	printf("\n\n");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%p ", &(Vinit_ptr[i][j]));
			printf("\t\t");
		}
		printf("\n\n");
	}
}