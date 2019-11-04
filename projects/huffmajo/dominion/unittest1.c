#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/***********************************************************
* void assert(int expected, int actual)
* expected: the determined correct answer
* actual: the calculated answer
*
* Returns nothing. Prints "Test passed" if expected and actual
* result are the same. Prints "Test failed" otherwise.
************************************************************/
void assert(int expected, int actual)
{
	if (expected == actual)
	{
		printf("Test passed\n");
	}
	else
	{
		printf("Test failed\n");
	}
}
