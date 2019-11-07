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
	int handPos;
	int player = 0;
	int opponent = 1;

	// initialize game
	initializeGame(numPlayers, k, seed, &base);
	base.hand[player][0] = tribute; // load hand with a tribute and 4 estates
	base.hand[player][1] = estate;
	base.hand[player][2] = estate;
	base.hand[player][3] = estate;
	base.hand[player][4] = estate;

	// start testing
	printf("***************************\n* Tribute Unit Test Start *\n***************************\n");

	printf("\nTEST 1: Top 2 cards of opponents deck are coppers\n");
	base.deck[opponent][base.deckCount[opponent] - 1] = copper;	// load top two card as coppers
	base.deck[opponent][base.deckCount[opponent] - 2] = copper;
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	handPos = 0; // hand position of tribute
	tributeEffect(&test, handPos, player); // play card

	// coins should be +2
	printf("Coins increase by +2\n");
	testAssert(base.coins + 2, test.coins);

	// opponents discard pile has 2 cards
	printf("Opponents discards those 2 cards\n");
	testAssert(base.discardCount[opponent] + 2, test.discardCount[opponent]);

	// actions is unchanged
	printf("Actions remain unchanged\n");
	testAssert(base.numActions, test.numActions);

	// hand contains 1 fewer
	printf("Hand size decreases by 1\n");
	testAssert(base.handCount[player] - 1, test.handCount[player]);

	printf("\nTEST 2: Top 2 cards of opponents deck are an action card and a victory card\n");
	base.deck[opponent][base.deckCount[opponent] - 1] = tribute;	// load top two card as tribute and estate
	base.deck[opponent][base.deckCount[opponent] - 2] = estate;
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	handPos = 0; // hand position of tribute
	tributeEffect(&test, handPos, player); // play card

	// coins should be unchanged
	printf("Coins remain the same\n");
	testAssert(base.coins, test.coins);

	// opponents discard pile has 2 cards
	printf("Opponents discards those 2 cards\n");
	testAssert(base.discardCount[opponent] + 2, test.discardCount[opponent]);

	// actions gets +2
	printf("Actions increase by 2\n");
	testAssert(base.numActions + 2, test.numActions);

	// hand contains 1  more
	printf("Hand size increases by 1\n");
	testAssert(base.handCount[player] + 1, test.handCount[player]);

	printf("\nTEST 3: Opponent has no cards in deck, discard or hand\n");
	base.deckCount[opponent] = 0;	// remove all cards from opponents deck, discard and hand
	base.handCount[opponent] = 0;
	base.discardCount[opponent] = 0;
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	handPos = 0; // hand position of tribute
	tributeEffect(&test, handPos, player); // play card

	// coins remain the same
	printf("Coins remain the same\n");
	testAssert(base.coins, test.coins);

	// opponents has nothing to discard
	printf("Opponent has nothing in discard\n");
	testAssert(base.discardCount[opponent], test.discardCount[opponent]);

	// actions is unchanged
	printf("Actions remain unchanged\n");
	testAssert(base.numActions, test.numActions);

	// hand contains 1 fewer
	printf("Hand size decreases by 1\n");
	testAssert(base.handCount[player] - 1, test.handCount[player]);

	printf("\nTEST 4: Opponent has 1 treasure card in deck, no cards in discard\n");
	base.deckCount[opponent] = 1;	// opponent has one card in deck, and 0 in discard
	base.handCount[opponent] = 0;
	base.discardCount[opponent] = 0;
	base.deck[opponent][base.deckCount[opponent] - 1] = copper;
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	handPos = 0; // hand position of tribute
	tributeEffect(&test, handPos, player); // play card

	// coins should be +2
	printf("Coins increase by +2\n");
	testAssert(base.coins + 2, test.coins);

	// opponents discard pile has 2 cards
	printf("Opponents discards that 1 card\n");
	testAssert(base.discardCount[opponent] + 1, test.discardCount[opponent]);

	// actions is unchanged
	printf("Actions remain unchanged\n");
	testAssert(base.numActions, test.numActions);

	// hand remains unchanged
	printf("Hand size does not change\n");
	testAssert(base.handCount[player], test.handCount[player]);

	printf("\nTEST 5: Opponent has 1 treasure card in discard pile, no cards in deck\n");
	base.deckCount[opponent] = 0;	// opponent has one card in discard, and 0 in deck
	base.handCount[opponent] = 0;
	base.discardCount[opponent] = 1;
	base.discard[opponent][base.discardCount[opponent] - 1] = copper;
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	handPos = 0; // hand position of tribute
	tributeEffect(&test, handPos, player); // play card

	// coins should be +2
	printf("Coins increase by +2\n");
	testAssert(base.coins + 2, test.coins);

	// opponents discard pile has 2 cards
	printf("Opponents discards that 1 card\n");
	testAssert(base.discardCount[opponent] + 1, test.discardCount[opponent]);

	// actions is unchanged
	printf("Actions remain unchanged\n");
	testAssert(base.numActions, test.numActions);

	// hand remains unchanged
	printf("Hand size does not change\n");
	testAssert(base.handCount[player], test.handCount[player]);

	printf("Unit Test Complete\n");

	return 0;
}
