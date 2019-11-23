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
	int player = 0;

	// initialize game
	initializeGame(numPlayers, k, seed, &base);

	// start testing
	printf("*************************\n* Baron Unit Test Start *\n*************************\n");

	// choose not to discard an estate, draw an estate
	printf("\nTEST 1: Play Baron and choose not to discard an estate\n");
	base.hand[player][0] = baron; // load hand with a baron and an estate
	base.hand[player][1] = estate;
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 0; // don't discard estate
	baronEffect(player, &test, choice1); // play card

	// check that coins didn't change
	printf("Check that coins weren't added\n");
	testAssert(base.coins, test.coins);

	// check that estate was not added to discard pile, only baron
	printf("Check that only the baron card was discarded\n");
	testAssert(base.discardCount[player] + 1, test.discardCount[player]);

	// check that estate card stack is one fewer than start
	printf("Check that estate supply is 1 fewer than at start\n");
	testAssert(base.supplyCount[estate] - 1, test.supplyCount[estate]);

	// check that drawn estate replaces played baron
	printf("Hand size should not change, drawn estate replaces played baron\n");
	testAssert(base.handCount[player], test.handCount[player]);

	// check that buys is increased by 1
	printf("Check that buys increased by 1\n");
	testAssert(base.numBuys + 1, test.numBuys);

	printf("\nTEST 2: Play Baron and choose to discard an estate with an estate in hand\n");
	base.hand[player][0] = baron; // load hand with a baron and an estate
	base.hand[player][1] = estate;
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // discard estate, gain 4 coins
	baronEffect(player, &test, choice1); // play card

	// check that coins increased by 4
	printf("Check that 4 coins were added\n");
	testAssert(base.coins + 4, test.coins);

	// check that estate and baron were discarded
	printf("Check that baron and estate were added to discard pile\n");
	testAssert(base.discardCount[player] + 2, test.discardCount[player]);

	// check that estate was removed from hand
	printf("Check that estate and baron were removed from hand\n");
	testAssert(base.handCount[player] - 2, test.handCount[player]);

	// check that estate supply is same
	printf("Check that estate supply is untouched\n");
	testAssert(base.supplyCount[estate], test.supplyCount[estate]);

	// check that buys in increased by 1
	printf("Check that buys increased by 1\n");
	testAssert(base.numBuys + 1, test.numBuys);

	printf("\nTEST 3: Play Baron and choose to discard an estate WITHOUT an estate in hand\n");
	base.hand[player][0] = baron; // load hand with baron and 4 coppers, NO estates
	base.hand[player][1] = copper;
	base.hand[player][2] = copper;
	base.hand[player][3] = copper;
	base.hand[player][4] = copper;
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // try to discard estate
	baronEffect(player, &test, choice1); // play card

	// check that coins didn't change
	printf("Check that coins weren't added\n");
	testAssert(base.coins, test.coins);

	// check that baron card is not in hand
	printf("Hand size should remain the same, drawn estate replaces discarded baron. \n");
	testAssert(base.handCount[player], test.handCount[player]);

	// check that one estate card was depleted from stack
	printf("Check that estate supply count is depleted by 1\n");
	testAssert(base.supplyCount[estate] - 1, test.supplyCount[estate]);

	// check that buys are increased by 1
	printf("Check that buys increased by 1\n");
	testAssert(base.numBuys + 1, test.numBuys);

	printf("Unit Test Complete\n");

	return 0;
}
