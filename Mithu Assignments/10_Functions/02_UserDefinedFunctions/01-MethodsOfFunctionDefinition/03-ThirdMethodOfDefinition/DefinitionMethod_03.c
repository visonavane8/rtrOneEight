#include <stdio.h> 
int main(int vinit_argc, char *vinit_argv[], char *vinit_envp[])
{
	void vinit_MyAddition(int, int);
	int vinit_a, vinit_b;
	printf("Enter Integer Value For 'A' : ");
	scanf("%d", &vinit_a);
	printf("Enter Integer Value For 'B' : ");
	scanf("%d", &vinit_b);
	MyAddition(vinit_a, vinit_b); 
	return(0);
}


void MyAddition(int vinit_a, int vinit_b) 
{	
	int vinit_sum;
	vinit_sum = vinit_a + vinit_b;
	printf("\n\n");
	printf("Sum Of %d And %d = %d\n\n", vinit_a, vinit_b, vinit_sum);
}

