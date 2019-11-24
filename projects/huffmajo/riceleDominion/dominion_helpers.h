#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);


int discardHand(int handPos, int currentPlayer, struct gameState* state);
/* This function discards a player's entire hand */

int drawCards(int player, int cardsToDraw, struct gameState* state);
/* Draws and adds a specified number of cards into the player's hand */

int checkEstateSupply(int estate, struct gameState* state);
/* Checks estates remaining in supply pile to determine if game is over */

// Used for Joel's testing
int cardType(int card);
void testAssert(int expected, int actual);
int testPass(int expected, int actual);

#endif
