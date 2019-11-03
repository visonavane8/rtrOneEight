#include <stdio.h> 
int main(int vinit_argc, char *vinit_argv[], char *vinit_envp[])
{
	int vinit_MyAddition(int, int);	
	int vinit_a, vinit_b, vinit_result;
	printf("Enter Integer Value For 'A' : ");
	scanf("%d", &vinit_a);
	printf("\n\n");
	printf("Enter Integer Value For 'B' : ");
	scanf("%d", &vinit_b);
	vinit_result = vinit_MyAddition(vinit_a, vinit_b); 
	printf("\n\n");
	printf("Sum Of %d And %d = %d\n\n", vinit_a, vinit_b, vinit_result);
	return(0);
}

int MyAddition(int vinit_a, int vinit_b) 
{
	int vinit_sum;
	vinit_sum = vinit_a + vinit_b;
	return(vinit_sum);
}