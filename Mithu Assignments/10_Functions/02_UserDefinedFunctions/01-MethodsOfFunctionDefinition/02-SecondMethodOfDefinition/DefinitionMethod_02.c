#include <stdio.h>
int main(int vinit_argc, char *vinit_argv[], char *vinit_envp[])
{
	int vinit_MyAddition(void);
	int vinit_result;
	vinit_result=vinit_MyAddition(); 
	printf("Sum = %d\n\n", vinit_result);
	return(0);
}

void vinit_MyAddition(void) 
{
	int vinit_a, vinit_b, vinit_sum;
	printf("Enter Integer Value For 'A' : ");
	scanf("%d", &vinit_a);

	printf("\n\n");
	printf("Enter Integer Value For 'B' : ");
	scanf("%d", &vinit_b);

	vinit_sum = vinit_a + vinit_b;
	return vinit_sum;
	printf("\n\n");
	
}
