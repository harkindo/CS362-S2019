/* -----------------------------------------------------------------------
 * Test for the village card that runs when the cardEffect function is called
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "village"

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
    bool testPassed = true;

	int i;

	int prevHandCount[MAX_PLAYERS];
	int prevPlayedCount;

   	struct gameState G;
    int seed = 1000;
    int numPlayers = 3;
    int currentPlayer = 0;
    int handPos = 0;
	int oldNumActions;
    int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
    			sea_hag, tribute, smithy, adventurer};


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    G.hand[currentPlayer][handPos] = village;

	// Store prevHandCount and prevPlayedCount
	for (i=0;i<numPlayers;i++){
		prevHandCount[i] = G.handCount[i];
	}
	prevPlayedCount = G.playedCardCount;

	oldNumActions = G.numActions;


	// Assert cardEffect returns 0
	if (!assertTrue(cardEffect(village, 0, 0, 0, &G, handPos, NULL) == 0,
	"village returns 0"))
		testPassed = false;

	// Assert each player gets the proper number of cards
	for (i=0;i<numPlayers;i++){
		if (i != currentPlayer){
			if (!assertTrue(prevHandCount[i] == G.handCount[i],
				"non-current players get +0 card"))
				testPassed = false;
		}
		else {
			if (!assertTrue(prevHandCount[i] == G.handCount[i],
				"current player gets +1 cards (then discards village card)"))
				testPassed = false;
		}
	}

    // Assert two more actions are added
    if (!assertTrue(G.numActions == oldNumActions + 2,
        "Two actions added"))
        testPassed = false;

	// Assert the village card was discarded
	if (!assertTrue(G.playedCardCount == prevPlayedCount+1,
		"village discarded after play") )
		testPassed = false;

    if (testPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
