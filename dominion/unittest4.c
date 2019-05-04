/* -----------------------------------------------------------------------
 * Unit test for the baronEffect function which handles when a
 * baron card is played.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "baron"

bool assertTrue(bool b, char * errMsg){
    if (b) {
        return true;
    }
    else {
        printf("Fail: did not assert '%s'\n", errMsg);
        return false;
    }
}

int main() {
    bool unitTestPassed = true;

	int i;

   	struct gameState G, testG;

    int seed = 1000;
    int numPlayers = 3;
	int oldCoins;
	int oldSupply;
    int currentPlayer = 0;
    int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
    			sea_hag, tribute, smithy, adventurer};


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));

	//set first card in hand to baron, and set number of cards in hand to 1
	testG.hand[currentPlayer][0] = baron;
	testG.handCount[currentPlayer] = 1;

	oldCoins = testG.coins;
	oldSupply = testG.supplyCount[estate];

	// Call barron effect and attempt to discard an estate
	if (!assertTrue(baronEffect(&testG, 0, 1) == 0,
		"baronEffect returns 0 (1)"))
		unitTestPassed = false;

	if (!assertTrue(testG.supplyCount[estate] == oldSupply - 1,
		"Estate card supply decreased by 1 (1)"))
		unitTestPassed = false;

	if (!assertTrue(testG.coins == oldCoins,
		"Coins did not increase when estate drawn (1)"))
		unitTestPassed = false;

	memcpy(&testG, &G, sizeof(struct gameState));

	//set first card in hand to baron. Do not attempt to exchange an estate
	testG.hand[currentPlayer][0] = baron;

	oldCoins = testG.coins;
	oldSupply = testG.supplyCount[estate];

	// Call barron effect and draw an estate
	if (!assertTrue(baronEffect(&testG, 0, 0) == 0,
		"baronEffect returns 0 (2)"))
		unitTestPassed = false;

	if (!assertTrue(testG.supplyCount[estate] == oldSupply - 1,
		"Estate card supply decreased by 1 (2)"))
		unitTestPassed = false;

	if (!assertTrue(testG.coins == oldCoins,
		"Coins did not increase when estate drawn (2)"))
		unitTestPassed = false;

	memcpy(&testG, &G, sizeof(struct gameState));

	//set first card in hand to baron and second card to estate. exchange Estate
	//for coins
	testG.hand[currentPlayer][0] = baron;
	testG.hand[currentPlayer][1] = estate;

	oldCoins = testG.coins;
	oldSupply = testG.supplyCount[estate];

	// Call barron effect and draw an estate
	if (!assertTrue(baronEffect(&testG, 0, 1) == 0,
		"baronEffect returns 0 (3)"))
		unitTestPassed = false;

	if (!assertTrue(testG.supplyCount[estate] == oldSupply,
		"Estate card supply did not decreased"))
		unitTestPassed = false;

	if (!assertTrue(testG.coins == oldCoins + 4,
		"+4 coins recieved"))
		unitTestPassed = false;


    if (unitTestPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
