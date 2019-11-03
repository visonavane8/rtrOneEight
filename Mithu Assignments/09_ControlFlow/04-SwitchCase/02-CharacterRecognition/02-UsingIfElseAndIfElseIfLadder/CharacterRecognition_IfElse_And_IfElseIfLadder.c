#include<stdio.h> 

#define CHAR_ALPHABET_UPPER_CASE_BEGINNING 65     
#define CHAR_ALPHABET_UPPER_CASE_ENDING 90

#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 97		 
#define CHAR_ALPHABET_LOWER_CASE_ENDING 122		 

#define CHAR_DIGIT_BEGINNING 48		 
#define CHAR_DIGIT_ENDING 57		 

int main(void)
{
	char ch;
	int ch_value;

	printf("Enter Character :");
	ch = getchar();

	if ((ch == 'A' || ch == 'a') || (ch == 'E' || ch == 'e') || (ch == 'I' || ch == 'i') || (ch == 'O' || ch == 'o') || (ch == 'U' || ch == 'u'))
	{
		printf("Character \'%c\' Entered By You, is A Vowel Character from The English Alphabet \n",ch);
	}

	else
	{
		ch_value = (int)ch;
		if ((ch_value >= CHAR_ALPHABET_UPPER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_UPPER_CASE_ENDING) || (ch_value >= CHAR_ALPHABET_LOWER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_LOWER_CASE_ENDING))
		{
			printf("Character \'%c\' Entered By You, is A Consonant Character From The English Alphabet \n",ch);
		}

		else if (ch_value >= CHAR_DIGIT_BEGINNING && ch_value <= CHAR_DIGIT_ENDING)
		{
			printf("Character \'%c\' Entered By You, is A Digit Character \n",ch);
		}

		else
		{
			printf("Character \'%c\' Entered By You, is A Special Character \n",ch);
		}
	}

	return 0;
}
