#include <stdio.h> 
int main(int vinit_argc, char *vinit_argv[], char *vinit_envp[])
{
	//function prototypes OR declarations
	void vinit_MyAddition(void);
	int vinit_MySubtraction(void);
	void vinit_MyMultiplication(int, int);
	int vinit_MyDivision(int, int);

	//variable declarations
	int vinit_result_subtraction;
	int vinit_a_multiplication, vinit_b_multiplication;
	int vinit_a_division, vinit_b_division, vinit_result_division;

	// *** ADDITION ***
	vinit_MyAddition(); //function call

	// *** SUBTRACTION ***
	vinit_result_subtraction = vinit_MySubtraction();
	printf("\n\n");
	printf("Subtraction Yields Result = %d\n", vinit_result_subtraction);

	// *** MULTIPLICATION ***
	printf("\n\n");
	printf("Enter Integer Value For 'A' For Multiplication : ");
	scanf("%d", &vinit_a_multiplication);

	printf("\n\n");
	printf("Enter Integer Value For 'B' For Multiplication : ");
	scanf("%d", &vinit_b_multiplication);

	vinit_MyMultiplication(vinit_a_multiplication, vinit_b_multiplication); 

	// *** DIVISION ***
	printf("\n\n");
	printf("Enter Integer Value For 'A' For Division : ");
	scanf("%d", &vinit_a_division);

	printf("\n\n");
	printf("Enter Integer Value For 'B' For Division : ");
	scanf("%d", &vinit_b_division);

	vinit_result_division = vinit_MyDivision(vinit_a_division, vinit_b_division); 
	printf("\n\n");
	printf("Division Of %d and %d Gives = %d (Quotient)\n", vinit_a_division, vinit_b_division, vinit_result_division);

	printf("\n\n");

	return(0);
}

void vinit_MyAddition(void) 
{
	int vinit_a, vinit_b, vinit_sum;
	printf("\n\n");
	printf("Enter Integer Value For 'A' For Addition : ");
	scanf("%d", &vinit_a);
	printf("\n\n");
	printf("Enter Integer Value For 'B' For Addition : ");
	scanf("%d", &vinit_b);
	vinit_sum = vinit_a + vinit_b;
	printf("\n\n");
	printf("Sum Of %d And %d = %d\n\n", vinit_a, vinit_b, vinit_sum);
}

int vinit_MySubtraction(void) 
{
	int vinit_a, vinit_b, vinit_subtraction;
	printf("\n\n");
	printf("Enter Integer Value For 'A' For Subtraction : ");
	scanf("%d", &vinit_a);
	printf("\n\n");
	printf("Enter Integer Value For 'B' For Subtraction : ");
	scanf("%d", &vinit_b);
	vinit_subtraction = vinit_a - vinit_b;
	return(vinit_subtraction);
}


void vinit_MyMultiplication(int vinit_a, int vinit_b) 
{
	int vinit_multiplication;
	vinit_multiplication = vinit_a * vinit_b;
	printf("\n\n");
	printf("Multiplication Of %d And %d = %d\n\n", vinit_a, vinit_b, vinit_multiplication);
}
int vinit_MyDivision(int vinit_a, int vinit_b) 
{
	int vinit_division_quotient;
	if (vinit_a > vinit_b)
		vinit_division_quotient = vinit_a / vinit_b;
	else
		vinit_division_quotient = vinit_b / vinit_a;

	return(vinit_division_quotient);
}
