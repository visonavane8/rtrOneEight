#include <stdio.h>
int main(void)
{
	float f;
	float f_num = 1.7f; //simply change this value ONLY to get different outputs...
	printf("Printing Numbers %f to %f : \n\n", f_num, (f_num * 10.0f));

	f = f_num;
	do
	{
		printf("\t%f\n", f);
		f = f + f_num;
	}while (f <= (f_num * 10.0f));

	return 0;
}
