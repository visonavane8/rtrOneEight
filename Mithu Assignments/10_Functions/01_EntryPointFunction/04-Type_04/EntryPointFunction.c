#include <stdio.h> 

int main(int vinit_argc, char *vinit_argv[])
{
	int vinit_i;
	printf("Hello World \n"); 
	printf("Number Of Command Line Arguments = %d\n\n", vinit_argc);
	
	printf("Command Line Arguments Passed To This Program Are : \n\n");
	for (vinit_i = 0; vinit_i < vinit_argc; vinit_i++)
	{
		printf("Command Line Argument Number %d = %s\n", (vinit_i + 1),vinit_argv[i]);
	}
	printf("\n\n");
	return(0);
}

