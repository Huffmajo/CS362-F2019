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
	int opponent = 1;

	// initialize game
	initializeGame(numPlayers, k, seed, &base);
	base.hand[player][0] = ambassador; // load hand with an ambassador and 4 estates
	base.hand[player][1] = estate;
	base.hand[player][2] = estate;
	base.hand[player][3] = estate;
	base.hand[player][4] = estate;

	// start testing
	printf("******************************\n* Ambassador Unit Test Start *\n******************************\n");

	printf("\nTEST 1: Trash 1 estate from hand. Opponent gains a copy\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // hand position of estate card to trash
	choice2 = 1; // number of copies of estate to trash
	handPos = 0; // hand position of ambassador
	ambassadorEffect(handPos, player, &test, choice1, choice2); // play card

	// check coins unchanged
	printf("Check coins are unchanged\n");
	testAssert(base.coins, test.coins);

	// check hand size decreased by two
	printf("Hand size is 2 fewer\n");
	testAssert(base.handCount[player] - 2, test.handCount[player]);

	// check opponent gained copy of card
	printf("Opponent gained 1 copy of card\n");
	testAssert(base.discardCount[opponent] + 1, test.discardCount[opponent]);

	// stack of card should be unchanged
	printf("Stack of estates should be unchanged\n");
	testAssert(base.supplyCount[estate], test.supplyCount[estate]);

	// ambassador discarded
	printf("Ambassador discarded\n");
	testAssert(base.discardCount[player] + 1, test.discardCount[player]);

	printf("\nTEST 2: Play ambassador and trash 0 estates.\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // hand position of estate card to trash
	choice2 = 0; // number of copies of estate to trash
	handPos = 0; // hand position of ambassador
	ambassadorEffect(handPos, player, &test, choice1, choice2); // play card

	// check coins unchanged
	printf("Check coins are unchanged\n");
	testAssert(base.coins, test.coins);

	// check hand size decreased by 1
	printf("Hand size decreased by 1\n");
	testAssert(base.handCount[player] - 1, test.handCount[player]);

	// check opponent discard unchanged
	printf("Opponent didn't gain any cards\n");
	testAssert(base.discardCount[opponent], test.discardCount[opponent]);

	// stack of card should be unchanged
	printf("Stack of estates should be unchanged\n");
	testAssert(base.supplyCount[estate], test.supplyCount[estate]);

	// ambassador discarded
	printf("Ambassador discarded\n");
	testAssert(base.discardCount[player] + 1, test.discardCount[player]);

	printf("\nTEST 3: Play ambassador and trash 2 estates\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // hand position of estate card to trash
	choice2 = 2; // number of copies of estate to trash
	handPos = 0; // hand position of ambassador
	ambassadorEffect(handPos, player, &test, choice1, choice2); // play card

	// check coins unchanged
	printf("Check coins are unchanged\n");
	testAssert(base.coins, test.coins);

	// check hand size reduced by 3
	printf("Hand size reduced by 3\n");
	testAssert(base.handCount[player] - 3, test.handCount[player]);

	// check opponent discard for 1 more card
	printf("Opponent gains estate in discard\n");
	testAssert(base.discardCount[opponent] + 1, test.discardCount[opponent]);

	// stack of card should increment
	printf("Stack of estates should have 1 more\n");
	testAssert(base.supplyCount[estate] + 1, test.supplyCount[estate]);

	// ambassador discarded
	printf("Ambassador discarded\n");
	testAssert(base.discardCount[player] + 1, test.discardCount[player]);

	printf("\nTEST 4: Play ambassador and try to trash this ambassador\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 0; // hand position of estate card to trash
	choice2 = 1; // number of copies of estate to trash
	handPos = 0; // hand position of ambassador
	returnState = ambassadorEffect(handPos, player, &test, choice1, choice2); // play card

	// function should return -1
	printf("Function fails with -1\n");
	testAssert(-1, returnState);

	printf("\nTEST 5: Play ambassador and try to trash more than 2 estates\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // hand position of estate card to trash
	choice2 = 3; // number of copies of estate to trash
	handPos = 0; // hand position of ambassador
	returnState = ambassadorEffect(handPos, player, &test, choice1, choice2); // play card

	// function should return -1
	printf("Function fails with -1\n");
	testAssert(-1, returnState);

	printf("\nTEST 6: Play ambassador and try to trash -1 estates\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // hand position of estate card to trash
	choice2 = -1; // number of copies of estate to trash
	handPos = 0; // hand position of ambassador
	returnState = ambassadorEffect(handPos, player, &test, choice1, choice2); // play card

	// function should return -1
	printf("Function fails with -1\n");
	testAssert(-1, returnState);

	printf("Unit Test Complete\n");

	return 0;
}
