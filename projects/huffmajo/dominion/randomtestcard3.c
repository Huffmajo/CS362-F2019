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
	int handPos, player, nextPlayer, numPlayers, handSize;
	int m;

	// setup test variables
	int numLoops = 10000;
	int test1Fails = 0;
	int test2Fails = 0;
	int test3Fails = 0;
	int tributeDiscarded = 0;
	int reveal1, reveal2;
	int j = 0;

	// start testing
	printf("***********************\n* Tribute Random Test *\n***********************\n");
	for (int i = 0; i < numLoops; i++)
	{
		// randomize variables to initialize game with
		numPlayers = rand() % 3 + 2;	// 1-4 players

		// initialize game
		initializeGame(numPlayers, k, seed, &pre);

		// set up rest of random values
		player = rand() % numPlayers; // current player = 0-numPlayers
		nextPlayer = getNextPlayer(player, &pre);	// designate next player after current
		handSize = pre.handCount[player] = rand() % 11;	// hand size = 0-10
		pre.handCount[player] = handSize;	// assign randomized handSize
		handPos = rand() % (handSize + 1);	// position of minion card = 0-(handSize-1)
		pre.deckCount[nextPlayer] = rand() % 31; // deck size of opponent = 0-30
		pre.discardCount[nextPlayer] = rand() % 31; // discard size of opponent = 0-30

		// put random cards in player's hand
		for (m = 0; m < pre.handCount[player]; m++)	// load hand with random cards
		{
			if (m == handPos)
			{
				pre.hand[player][m] = tribute; // tribute card is at handPos
			}
			else
			{
				pre.hand[player][m] = rand() % 27; // random card from all possible cards
			}
		}

		// put random cards in opponent's deck
		for (m = 0; m < pre.deckCount[nextPlayer]; m++)
		{
			pre.deck[nextPlayer][m] = rand() % 27; // random card from all possible cards
		}

		// put random cards in opponent's discard
		for (m = 0; m < pre.discardCount[nextPlayer]; m++)
		{
			pre.discard[nextPlayer][m] = rand() % 27; // random card from all possible cards
		}

		// get cardtypes of cards to be revealed from opponents deck
		// 0 = other
		// 1 = treasure
		// 2 = victory
		// 3 = action
		reveal1 = cardType(pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1]);
		reveal2 = cardType(pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 2]);

		// copy game state
		memcpy(&post, &pre, sizeof(struct gameState));

		// run card function on post state
		tributeEffect(&post, handPos, player);

		// run tests
		// TEST 1: Tribute discarded
		tributeDiscarded = 0;

		// check all cards in discard for a tribute
		while (tributeDiscarded == 0 && j < post.discardCount[player])
		{
			if(post.discard[player][j] == tribute)
			{
				tributeDiscarded = 1;
			}
			j++;
		}

		if (tributeDiscarded == 0)
		{
			test1Fails++;
		}

		// TEST 2: Drawn cards are the same type
		if (reveal1 == reveal2)
		{
			// treasure cards, +2 coins
			if (reveal1 == 1)
			{
				if (testPass(pre.coins + 2, post.coins) == 0)
				{
					test2Fails++;
				}
			}
			// victory cards, +2 cards
			else if (reveal1 == 2)
			{
				if (testPass(pre.handCount[player] + 2, post.handCount[player]) == 0)
				{
					test2Fails++;
				}
			}
			// action cards, +2 actions
			else if (reveal1 == 3)
			{
				if (testPass(pre.numActions + 2, post.numActions) == 0)
				{
					test2Fails++;
				}
			}
			// otherwise cards are curses, nothing changes
			else
			{
				if ((testPass(pre.coins, post.coins) == 0) || (testPass(pre.handCount[player], post.handCount[player]) == 0) || (testPass(pre.numActions, post.numActions) == 0))
				{
					test2Fails++;
				}
			}
		}

		// TEST 3: No cards in next player's deck
		if (pre.deckCount[nextPlayer] == 0)
		{
				if ((testPass(pre.coins, post.coins) == 0) || (testPass(pre.handCount[player], post.handCount[player]) == 0) || (testPass(pre.numActions, post.numActions) == 0))
				{
					test3Fails++;
				}
		}
	}

	// print results
	printf("TEST 1: Tribute put in discard: %d fails\n", test1Fails);
	printf("TEST 2: Drawn cards are the same type: %d fails\n", test2Fails);
	printf("TEST 3: No cards in next player's deck: %d fails\n", test3Fails);

	return 0;
}
