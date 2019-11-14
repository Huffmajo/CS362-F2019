#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"


int main()
{
	// seed randomization
	srand(time(NULL));

	// setup variables
	struct gameState pre, post;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	int choice1, player, numPlayers;
	int m;

	// setup test variables
	int numLoops = 10000;
	int test1Fails = 0;
	int test2Fails = 0;
	int test3Fails = 0;
	int baronDiscarded = 0;
	int j = 0;

	// start timer
	clock_t start, end;
	start = clock();

	// start testing
	printf("*********************\n* Baron Random Test *\n**********************\n");
	for (int i = 0; i < numLoops; i++)
	{
		// randomize variables to initialize game with
		numPlayers = rand() % 3 + 2;	// 1-4 players

		// initialize game
		initializeGame(numPlayers, k, seed, &pre);

		// set up rest of random values
		choice1 = rand() % 2;	// choice1 = 0-1
		player = rand() % numPlayers; // current player = 0-numPlayers
		pre.handCount[player] = rand() % 11;	// hand size = 0-10
		for (m = 0; m < pre.handCount[player]; m++)	// load hand with random cards
		{
			pre.hand[player][m] = rand() % 27; // random card from all possible cards
		}

		// copy game state
		memcpy(&post, &pre, sizeof(struct gameState));

		// run card function on post state
		baronEffect(&post, choice1, player);

		// run tests
		// Test 1: Buys incremented by 1
		if (testPass(pre.numBuys + 1, post.numBuys) == 0)
		{
			test1Fails++;
		}

		// TEST 2: Baron discarded
		baronDiscarded = 0;

		// check all cards in discard for a baron
		while (baronDiscarded == 0 && j < post.discardCount[player])
		{
			if(post.discard[player][j] == baron)
			{
				baronDiscarded = 1;
			}
			j++;
		}

		if (baronDiscarded == 0)
		{
			test2Fails++;
		}

		// TEST 3: Number of actions unchanged
		if (testPass(pre.numActions, post.numActions) == 0)
		{
			test3Fails++;
		}
	}

	// stop timer and calculate time
	end = clock();
	double executeTime = ((double) (end - start)) / CLOCKS_PER_SEC;

	// print results
	printf("Runtime: %f seconds\n", executeTime);
	printf("TEST 1: +1 buys: %d fails\n", test1Fails);
	printf("TEST 2: Baron put in discard: %d fails\n", test2Fails);
	printf("TEST 3: Number of actions unchanged: %d fails\n", test3Fails);

	return 0;
}
