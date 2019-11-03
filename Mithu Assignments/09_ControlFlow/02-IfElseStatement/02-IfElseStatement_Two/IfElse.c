#include<stdio.h>
int main(void)
{
	int v_age;
	printf("Enter Age : ");
	scanf("%d",&v_age);
	if(v_age>=18)
	{
		printf("You Are Eligible For Voting \n");
	}
	else
	{
		printf("You Are Not Eligible For Voting \n");
	}
	return 0;
}
