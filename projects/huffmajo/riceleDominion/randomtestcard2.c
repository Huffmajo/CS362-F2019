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
	int choice1, choice2, handPos, player, numPlayers, handSize;
	int m;

	// setup test variables
	int numLoops = 10000;
	int test1Fails = 0;
	int test2Fails = 0;
	int test3Fails = 0;
	int minionDiscarded = 0;
	int j = 0;

	// start timer
	clock_t start, end;
	start = clock();

	// start testing
	printf("**********************\n* Minion Random Test *\n**********************\n");
	for (int i = 0; i < numLoops; i++)
	{
		// randomize variables to initialize game with
		numPlayers = rand() % 3 + 2;	// 1-4 players

		// initialize game
		initializeGame(numPlayers, k, seed, &pre);

		// set up rest of random values
		choice1 = rand() % 2;	// choice1 = 0-1
		choice2 = rand() % 2;	// choice2 = 0-1
		player = rand() % numPlayers; // current player = 0-numPlayers
		handSize = pre.handCount[player] = rand() % 11;	// hand size = 0-10
		handPos = rand() % (handSize + 1);	// position of minion card = 0-(handSize-1)

		for (m = 0; m < pre.handCount[player]; m++)	// load hand with random cards
		{
			if (m == handPos)
			{
				pre.hand[player][m] = minion; // minion card is at handPos
			}
			else
			{
				pre.hand[player][m] = rand() % 27; // random card from all possible cards
			}
		}

		// copy game state
		memcpy(&post, &pre, sizeof(struct gameState));

		// run card function on post state
		minionEffect(handPos, player, &post, choice1, choice2);

		// run tests
		// Test 1: Actions incremented by 1
		if (testPass(pre.numActions + 1, post.numActions) == 0)
		{
			test1Fails++;
		}

		// TEST 2: Minion discarded
		minionDiscarded = 0;

		// check all cards in discard for a minion
		while (minionDiscarded == 0 && j < post.discardCount[player])
		{
			if(post.discard[player][j] == minion)
			{
				minionDiscarded = 1;
			}
			j++;
		}

		if (minionDiscarded == 0)
		{
			test2Fails++;
		}

		// TEST 3: Number of buys unchanged
		if (testPass(pre.numBuys, post.numBuys) == 0)
		{
			test3Fails++;
		}
	}

	// stop timer and calculate time
	end = clock();
	double executeTime = ((double) (end - start)) / CLOCKS_PER_SEC;

	// print results
	printf("Runtime: %f seconds\n", executeTime);
	printf("TEST 1: +1 actions: %d fails\n", test1Fails);
	printf("TEST 2: Minion put in discard: %d fails\n", test2Fails);
	printf("TEST 3: Number of buys unchanged: %d fails\n", test3Fails);

	return 0;
}
