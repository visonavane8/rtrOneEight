#include<stdio.h>
int main(void)
{
	int v_age;
	printf("Enter age :");
	scanf("%d",&v_age);
	if(v_age>=18)
		printf("You are eligible for voting\n");
	printf("NOT ELIGIBLE FOR VOTING\n");
	return 0;
}
