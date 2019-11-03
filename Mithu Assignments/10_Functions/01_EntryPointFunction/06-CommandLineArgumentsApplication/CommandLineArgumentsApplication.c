#include <stdio.h> 
#include <ctype.h> 
int main(int vinit_argc, char *vinit_argv[], char *vinit_envp[])
{
	int i;
	int vinit_num;
	int vinit_sum = 0;

	printf("\n\n");
	printf("Sum Of All Integer Command Line Arguments Is : \n\n");
	for (i = 1; i < vinit_argc; i++) 
	{
		vinit_num = atoi(vinit_argv[i]);
		vinit_sum = vinit_sum + vinit_num;
	}

	printf("vinit_sum = %d\n\n", vinit_sum);

	return(0);
}
