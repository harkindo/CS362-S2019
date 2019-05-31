/* -----------------------------------------------------------------------
 * Unit test for the smithyEffect function which handles when a \
 * smithy card is played.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "smithy"

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

	int prevHandCount[MAX_PLAYERS];
	int prevPlayedCount;

   	struct gameState G;
    int seed = 1000;
    int numPlayers = 3;
    int currentPlayer = 0;
    int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
    			sea_hag, tribute, smithy, adventurer};


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

	// Store prevHandCount and prevPlayedCount
	for (i=0;i<numPlayers;i++){
		prevHandCount[i] = G.handCount[i];
	}
	prevPlayedCount = G.playedCardCount;

	// Assert the smithyEffect returns 0
	if (!assertTrue(smithyEffect(&G, 0) == 0, "Smithy returns 0"))
		unitTestPassed = false;

	// Assert each player gets the proper number of cards
	for (i=0;i<numPlayers;i++){
		if (i != currentPlayer){
			if (!assertTrue(prevHandCount[i] == G.handCount[i],
				"non-current players get +0 card"))
				unitTestPassed = false;
		}
		else {
			if (!assertTrue(prevHandCount[i] == G.handCount[i] - 2,
				"current player gets +3 cards (then discards 1 card)"))
				unitTestPassed = false;
		}
	}

	// Assert the smithy card was discarded
	if (!assertTrue(G.playedCardCount == prevPlayedCount+1,
		"smithy discarded after play") )
		unitTestPassed = false;

    if (unitTestPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
