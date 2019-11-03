#include<stdio.h>
int main()
{
	int v_num;
	printf("Enter value for v_num : ");
	scanf("%d",&v_num);

	if(v_num<0)
		printf("Num = %d is less than 0(NEG)\n",v_num);
	if((v_num>0) && (v_num<=100))
	        printf("Num = %d is between 0 and 100 \n",v_num);
	if((v_num>100) && (v_num<=200))
		printf("Num = %d is between 100 and 200\n",v_num);
	if((v_num>200) && (v_num<=300))
		printf("Num = %d is between 200 and 300\n",v_num);
	if((v_num>300) && (v_num<=400))
		printf("Num = %d is between 300 and 400\n",v_num);
	if((v_num>400) && (v_num<=500))
		printf("Num = %d is between 400 and 500\n",v_num);
	if(v_num>500)
		printf("Num = %d is greater than 500\n",v_num);

	return 0;
}
