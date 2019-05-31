/* -----------------------------------------------------------------------
 * Unit test for the mineEffect function which handles when a
 * mine card is played.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "mine"

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
    int oldNumSilvers = 0;
	int newNumSilvers = 0;
	int oldNumCoppers = 0;
	int newNumCoppers = 0;
    int seed = 1000;
    int numPlayers = 3;
    int currentPlayer = 0;
    int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
    			sea_hag, tribute, smithy, adventurer};


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));

	//set first card in hand to mine, second to adventurer.
	testG.hand[currentPlayer][0] = mine;
	testG.hand[currentPlayer][1] = adventurer;
	if (!assertTrue(cardEffect(mine, 1, gold, 0, &testG, 0, NULL) == -1,
		"Cannot exchange non-treasure cards"))
		unitTestPassed = false;

	// Set first card to mine second to copper to assert copper cannot be exchanged
	// for gold
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.hand[currentPlayer][0] = mine;
	testG.hand[currentPlayer][1] = copper;
    assertTrue(getCost(gold) == 6 && getCost(copper) == 0, "cost of gold is 6, copper 3");
	if (!assertTrue(cardEffect(mine, 1, gold, 0, &testG, 0, NULL) == -1,
		"Cannot exchange treasure for one with a value of more than +3"))
		unitTestPassed = false;

	// Set first card to mine second to copper to assert state after copper exchanged
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.hand[currentPlayer][0] = mine;
	testG.hand[currentPlayer][1] = copper;

	for (i=0;i<testG.handCount[currentPlayer];i++){
		if (testG.hand[currentPlayer][i] == silver)
			oldNumSilvers++;
		if (testG.hand[currentPlayer][i] == copper)
			oldNumCoppers++;
	}

	if (!assertTrue(cardEffect(mine, 1, silver, 0, &testG, 0, NULL) == 0,
		"Can exchange treasure for another one with a value of +3 or less"))
		unitTestPassed = false;


	for (i=0;i<testG.handCount[currentPlayer];i++){
		if (testG.hand[currentPlayer][i] == silver)
			newNumSilvers++;
		if (testG.hand[currentPlayer][i] == copper)
			newNumCoppers++;
	}
	if (!assertTrue(newNumSilvers == oldNumSilvers + 1,
		"One silver has been added to hand"))
		unitTestPassed = false;

	if (!assertTrue(newNumCoppers == oldNumCoppers - 1,
		"Copper has been removed from hand"))
		unitTestPassed = false;

    if (unitTestPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
