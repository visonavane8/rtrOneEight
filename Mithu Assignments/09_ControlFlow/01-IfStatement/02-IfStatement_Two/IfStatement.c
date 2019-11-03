#include<stdio.h>
int main()
{
	int v_age;

	printf("Enter Age : ");
	scanf("%d",&v_age);
	if(v_age>=18)
	{
		printf("You are eligible for voting\n");
	}

	return 0;
}
