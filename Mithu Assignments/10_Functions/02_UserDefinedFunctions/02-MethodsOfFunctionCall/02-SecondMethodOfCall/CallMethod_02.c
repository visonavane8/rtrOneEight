#include <stdio.h>
int main(int argc, char *argv[], char *envp[])
{
	//function prototypes
	void vinit_display_information(void);
	void vinit_Function_Country(void);

	//code
	vinit_display_information(); 
	vinit_Function_Country(); 

	return(0);
}

void vinit_display_information(void)
{
	void vinit_Function_My(void);
	void vinit_Function_Name(void);
	void vinit_Function_Is(void);
	void vinit_Function_FirstName(void);
	void vinit_Function_MiddleName(void);
	void vinit_Function_Surname(void);
	void vinit_Function_OfAMC(void);

	vinit_Function_My();
	vinit_Function_Name();
	vinit_Function_Is();
	vinit_Function_FirstName();
	vinit_Function_MiddleName();
	vinit_Function_Surname();
	vinit_Function_OfAMC();
}

void vinit_Function_My(void) 
{
	
	printf("\n\n");

	printf("My");
}

void vinit_Function_Name(void) 
{
	printf("\n\n");
	printf("Name");
}

void vinit_Function_Is(void) 
{
	printf("\n\n");
	printf("Is");
}

void vinit_Function_FirstName(void) 
{
	printf("\n\n");
	printf("Vinit");
}

void vinit_Function_MiddleName(void) 
{
	printf("\n\n");
	printf("Vijay");
}

void vinit_Function_Surname(void) 
{
	printf("\n\n");
	printf("Sonavane");
}
 
void vinit_Function_OfAMC(void)
{
	printf("\n\n");
	printf("Of RTR 2018");
}

void vinit_Function_Country(void)
{
	printf("\n\n");
	printf("I live In India.");
	printf("\n\n");
}
