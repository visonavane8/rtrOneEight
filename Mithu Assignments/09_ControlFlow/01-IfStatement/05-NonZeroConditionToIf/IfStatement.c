#include<stdio.h>
int main()
{
	int v_a;
	v_a=5;
	if(v_a)
		printf("if block 1 : A exist and has value = %d\n",v_a);

	v_a=-5;
	if(v_a)
		printf("if block 2 : A exist and has value = %d\n",v_a);
	v_a=0;
	if(v_a)
		printf("if block 3 : A exist and has value = %d\n",v_a);

	printf("All statements Done \n");
	return 0;
}
