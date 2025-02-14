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
	int choice1, choice2, handPos;
	int player = 0;
	int opponent = 1;

	// initialize game
	initializeGame(numPlayers, k, seed, &base);
	base.hand[player][0] = minion; // add minion card to hand

	// start testing
	printf("**************************\n* Minion Unit Test Start *\n**************************\n");

	printf("\nTEST 1: Play Minion and choose +2 coins action\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	choice1 = 1; // +2 coins
	choice2 = 0;
	handPos = 0; // position of minion card in hand
	minionEffect(handPos, player, &test, choice1, choice2); // play card

 	// check coins increased by 2
	printf("Check that +2 coins added\n");
	testAssert(base.coins + 2, test.coins);

	// check that minion was added to discard pile
	printf("Check that minion is in discard pile\n");
	testAssert(base.discardCount[player] + 1, test.discardCount[player]);

	// number of actions + 1
	printf("Check that number of actions increased by  1\n");
	testAssert(base.numActions + 1, test.numActions);

	printf("\nTEST 2: Play Minion and choose to discard hand and draw cards. Opponent has 5 cards in hand\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	base.hand[opponent][0] = minion; // fill opponents hand with 5 cards
	base.hand[opponent][1] = copper;
	base.hand[opponent][2] = copper;
	base.hand[opponent][3] = copper;
	base.hand[opponent][4] = copper;
	base.handCount[opponent] = 5;
	choice1 = 0; // discard hand and draw 4 cards
	choice2 = 1;
	handPos = 0; // position of minion card in hand
	minionEffect(handPos, player, &test, choice1, choice2); // play card

	// check coins are unchanged
	printf("Check that coins are unchanged\n");
	testAssert(base.coins, test.coins);

	// discard pile has number of cards in hand initially
	printf("Check hand was discarded\n");
	testAssert(base.handCount[player], test.discardCount[player]);

	// hand contains 4 cards
	printf("Check drew 4 cards\n");
	testAssert(4, test.handCount[player]);

	// other players hands contain 4 cards
	printf("Check opponents hand has 4 cards\n");
	testAssert(4, test.handCount[opponent]);

	// other players discard piles have 5 cards
	printf("Check opponent discarded 5 cards\n");
	testAssert(5, test.discardCount[opponent]);

	// number of actions + 1
	printf("Check that number of actions increased by  1\n");
	testAssert(base.numActions + 1, test.numActions);

	printf("\nTEST 3: Play Minion and choose to discard hand and draw cards. Opponent has no cards in hand\n");
	memcpy(&test, &base, sizeof(struct gameState)); // refresh test state
	base.hand[opponent][0] = -1; // empty opponents hand
	base.hand[opponent][1] = -1;
	base.hand[opponent][2] = -1;
	base.hand[opponent][3] = -1;
	base.hand[opponent][4] = -1;
	base.handCount[opponent] = 0;
	choice1 = 0; // discard hand and draw 4 cards
	choice2 = 1;
	handPos = 0; // position of minion card in hand
	minionEffect(handPos, player, &test, choice1, choice2); // play card

	// check coins are unchanged
	printf("Check that coins are unchanged\n");
	testAssert(base.coins, test.coins);

	// discard pile has number of cards in hand initially
	printf("Check hand was discarded\n");
	testAssert(base.handCount[player], test.discardCount[player]);

	// hand contains 4 cards
	printf("Check drew 4 cards\n");
	testAssert(4, test.handCount[player]);

	// other players hands are unchanged
	printf("Check opponents hand is unchanged\n");
	testAssert(base.handCount[opponent], test.handCount[opponent]);

	// other players discard piles unchanged
	printf("Check opponents discard pile is unchanged\n");
	testAssert(base.discardCount[opponent], test.discardCount[opponent]);

	// number of actions + 1
	printf("Check that number of actions increased by  1\n");
	testAssert(base.numActions + 1, test.numActions);

	printf("Unit Test Complete\n");

	return 0;
}

