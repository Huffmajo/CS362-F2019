#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	// valid ASCII characters are from 33 to 126
	char randomChar;
	randomChar = rand() % 94 + 32;
	return randomChar;
}

char *inputString()
{
	int stringLen = 6;
	char randomString[stringLen - 1];

	int i;
	for (i = 0; i < stringLen; i++)
	{
		// we only need to generate characters from 'e' to 't'
		randomString[i] =  rand() % 16 + 101;
	}
	randomString[5] = '\0';

	char* strPtr = randomString;
	return strPtr;
}

void testme()
{
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;
	while (1)
	{
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' '&& state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
			&& s[2] == 's' && s[3] == 'e'
			&& s[4] == 't' && s[5] == '\0'
			&& state == 9)
		{
			printf("error ");
			exit(200);
		}
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();

/*
	int i;
	int testLimit = 10;
	int allGood = 1;
	char* ender;

	// loop until failure or test complete
	for (i = 0; i < testLimit; i++)
	{
//		TEST inputString()
		char* str;
		strcpy(str, inputString());

		printf("%s\n", str);


//		TEST inputChar()

		char c = inputChar();

		if (i % 20 == 0)
		{
			printf("%c\n", c);
		}
		else
		{
			printf("%c ", c);

		}

	}
*/
	return 0;
}

