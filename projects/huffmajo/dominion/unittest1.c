#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

int main()
{
	// setup variables
	struct gameState base, test;
	int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	int choice1;

	// initialize game
	initializeGame(numPlayers, k, seed, &base);

	// start testing
	printf("*************************\n* Baron Unit Test Start *\n*************************\n");

	// choose not to discard an estate, draw an estate
	printf("\nTEST 1: Play Baron and choose not to discard an estate\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 0; // don't discard estate
	baronEffect(&test, choice1, 1); // play card

	// check that coins didn't change
	printf("Check that coins weren't added\n");
	testAssert(base.coins, test.coins);

	// check that estate was not added to discard pile
	printf("Check that no estate is in discard pile\n");
	testAssert(base.discardCount[1] + 1, test.discardCount[1]);

	// check that baron card is now in discard pile
	printf("Check that baron is in discard pile\n");
	testAssert(base.discardCount[1] + 1, test.discardCount[1]);

	// check that estate card stack is one fewer than start
	printf("Check that estate supply is 1 fewer than at start\n");
	testAssert(base.supplyCount[estate] - 1, test.supplyCount[estate]);

	// check that buys in increased by 1
	printf("Check that buys increased by 1\n");
	testAssert(base.numBuys + 1, test.numBuys);

	printf("\nTEST 2: Play Baron and choose to discard an estate with an estate in hand\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // discard estate, gain 4 coins
	addCardToHand(1, 1, &test); // add estate card to hand
	baronEffect(&test, choice1, 1); // play card

	// check that coins increased by 4
	printf("Check that 4 coins were added\n");
	testAssert(base.coins + 4, test.coins);

	// check that estate was added to discard pile
	printf("Check that estate was added to discard pile\n");
	testAssert(base.discardCount[1] + 1, test.discardCount[1]);

	// check that estate was removed from hand
	printf("Check that estate was removed from hand\n");
	testAssert(base.handCount[1], test.handCount[1]);

	// check that estate supply is decremented by one
	printf("Check that estate supply has two fewer than total\n");
	testAssert(base.supplyCount[estate] - 2, test.supplyCount[estate]);

	// check that buys in increased by 1
	printf("Check that buys increased by 1\n");
	testAssert(base.numBuys + 1, test.numBuys);

	printf("\nTEST 3: Play Baron and choose to discard an estate WITHOUT an estate in hand\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // try to discard estate
	baronEffect(&test, choice1, 1); // play card

	// check that coins didn't change
	printf("Check that coins weren't added\n");
	testAssert(base.coins, test.coins);

	// check that baron card is not in hand
	printf("Check that baron card is not in hand\n");
	testAssert(base.handCount[1], test.handCount[1]);

	// check that one estate card was depleted from stack
	printf("Check that estate supply count is depleted by 1\n");
	testAssert(base.supplyCount[estate] - 1, test.supplyCount[estate]);

	// check that buys are increased by 1
	printf("Check that buys increased by 1\n");
	testAssert(base.numBuys + 1, test.numBuys);

	printf("Unit Test Complete\n");

	return 0;
}
