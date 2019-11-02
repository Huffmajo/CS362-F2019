#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	// valid ASCII characters are from 33 to 126
	char randomChar;
	int randomInt;
	randomChar = rand() % 94 + 32;
	return randomChar;
}

char *inputString()
{
	// TODO: rewrite this function
	int stringLen = 5;
	char* randomString;

	int i;
	for (i = 0; i < stringLen; i++)
	{
		randomString[i] = inputChar();
	}

	return randomString;
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
//	testme();
	int i;
	int testLimit = 1001;
	int allGood = 1;
	char* ender;

	// loop until failure or test complete
	for (i = 0; i < testLimit; i++)
	{
//		char str[] = inputString();
/*
		if (i % 10 == 0)
		{
			ender = "\n";
		}
		else
		{
			ender = "\t";
		}
		printf("%s%s", inputString, ender);
*/
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

	return 0;
}

