#include <stdio.h> 

int main(int vinit_argc, char *vinit_argv[], char *vinit_envp[])
{
	int i;
	printf("Hello World \n"); 
	printf("Number Of Command Line Arguments = %d\n\n", vinit_argc);
	printf("Command Line Arguments Passed To This Program Are : \n\n");
	for (i = 0; i < vinit_argc; i++)
	{
		printf("Command Line Argument Number %d = %s\n", (i + 1),vinit_argv[i]);
	}
	printf("\n\n");

	printf("First 20 Environmental Variables Passed To This Program Are : \n\n");
	for (i = 0; i < 20; i++)
	{
		printf("Command Line Argument Number %d = %s\n", (i + 1), vinit_envp[i]);
	}
	printf("\n\n");
	return(0);
}

