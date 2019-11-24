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
	int choice1, choice2, handPos, returnState;
	int player = 0;

	// initialize game
	initializeGame(numPlayers, k, seed, &base);
	base.hand[player][0] = mine; // load hand with a mine, copper, silver, gold and an estate
	base.hand[player][1] = copper;
	base.hand[player][2] = silver;
	base.hand[player][3] = gold;
	base.hand[player][4] = estate;

	// start testing
	printf("************************\n* Mine Unit Test Start *\n************************\n");

	printf("\nTEST 1: Trash a copper to gain a silver\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // hand position of copper to trash
	choice2 = silver; // card to get in exchange
	handPos = 0; // hand position of mine
	mineEffect(handPos, player, &test, choice1, choice2); // play card

	// hand contains 1 fewer
	printf("Hand size decreases by 1\n");
	testAssert(base.handCount[player] - 1, test.handCount[player]);

	// trash card should be discarded
	printf("Discard count increases by 1\n");
	testAssert(base.discardCount[player] + 1, test.discardCount[player]);

	// actions unchanged
	printf("Number of actions unchanged\n");
	testAssert(base.numActions, test.numActions);

	// coins remain the same
	printf("Coins are unchanged\n");
	testAssert(base.coins, test.coins);

	printf("\nTEST 2: Trash a silver to get a duchy\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 2; // hand position of silver to trash
	choice2 = duchy; // card to get in exchange
	handPos = 0; // hand position of mine
	returnState = mineEffect(handPos, player, &test, choice1, choice2); // play card

	// should return -1
	printf("Can't trade for non-treasure card. Should return -1\n");
	testAssert(-1, returnState);

	// hand unchanged
	printf("Hand size unchanged\n");
	testAssert(base.handCount[player], test.handCount[player]);

	// discard should remain unchanged
	printf("Discard count unchanged\n");
	testAssert(base.discardCount[player], test.discardCount[player]);

	// actions unchanged
	printf("Number of actions unchanged\n");
	testAssert(base.numActions, test.numActions);

	// coins remain the same
	printf("Coins are unchanged\n");
	testAssert(base.coins, test.coins);

	printf("\nTEST 3: Trash estate for a copper\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 4; // hand position of estate to trash
	choice2 = copper; // card to get in exchange
	handPos = 0; // hand position of mine
	returnState = mineEffect(handPos, player, &test, choice1, choice2); // play card

	// should return -1
	printf("Can't trade non-treasure. Should return -1\n");
	testAssert(-1, returnState);

	// hand unchanged
	printf("Hand size unchanged\n");
	testAssert(base.handCount[player], test.handCount[player]);

	// discard should remain unchanged
	printf("Discard count unchanged\n");
	testAssert(base.discardCount[player], test.discardCount[player]);

	// actions unchanged
	printf("Number of actions unchanged\n");
	testAssert(base.numActions, test.numActions);

	// coins remain the same
	printf("Coins are unchanged\n");
	testAssert(base.coins, test.coins);

	printf("\nTEST 4: Trash gold copper to gain a gold\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 3; // hand position of copper to trash
	choice2 = gold; // card to get in exchange
	handPos = 0; // hand position of mine
	returnState = mineEffect(handPos, player, &test, choice1, choice2); // play card

	// should return 1
	printf("Gold for gold is a valid trade. should return 0\n");
	testAssert(0, returnState);

	// hand unchanged
	printf("Hand size unchanged\n");
	testAssert(base.handCount[player], test.handCount[player]);

	// discard should remain unchanged
	printf("Only mine card discarded\n");
	testAssert(base.discardCount[player] + 1, test.discardCount[player]);

	// actions unchanged
	printf("Number of actions unchanged\n");
	testAssert(base.numActions, test.numActions);

	// coins remain the same
	printf("Coins are unchanged\n");
	testAssert(base.coins, test.coins);

	printf("Unit Test Complete\n");

	return 0;
}
