#include <stdio.h>
int main(int vinit_argc, char *vinit_argv[], char *vinit_envp[])
{
	void vinit_MyAddition(void);
	vinit_MyAddition(); 
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

	 vinit_sum= vinit_a + vinit_b;

	printf("\n\n");
	printf("Sum Of %d And %d = %d\n\n",vinit_a, vinit_b, vinit_sum);
}
