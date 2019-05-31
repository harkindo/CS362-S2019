/* -----------------------------------------------------------------------
 * Test for the adventurer card that runs when the cardEffect function is called
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "adventurer"

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
    int oldNumTreasure=0;
    int newNumTreasure=0;
    int seed = 1000;
    int numPlayers = 3;
    int currentPlayer = 0;
    int handPos = 0;
    int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
    			sea_hag, tribute, smithy, adventurer};


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    G.hand[currentPlayer][handPos] = adventurer;

	// Store prevHandCount and prevPlayedCount
	for (i=0;i<numPlayers;i++){
		prevHandCount[i] = G.handCount[i];
	}
	prevPlayedCount = G.playedCardCount;

    // Get number of treasure cards initialy in hand
    for (i=0;i<G.handCount[currentPlayer];i++){
        if (G.hand[currentPlayer][i] == copper || G.hand[currentPlayer][i] == silver || G.hand[currentPlayer][i] == gold){
            oldNumTreasure++;
        }
    }


	// Assert cardEffect returns 0
	if (!assertTrue(cardEffect(adventurer, 0, 0, 0, &G, handPos, NULL) == 0,
	"adventurer returns 0"))
		testPassed = false;

	// Assert each player gets the proper number of cards
	for (i=0;i<numPlayers;i++){
		if (i != currentPlayer){
			if (!assertTrue(prevHandCount[i] == G.handCount[i],
				"non-current players get +0 card"))
				testPassed = false;
		}
		else {
			if (!assertTrue(prevHandCount[i] == G.handCount[i] - 1,
				"current player gets +2 cards (then discards adventurer card)"))
				testPassed = false;
		}
	}

    // Get number of treasure cards now in hand
    for (i=0;i<G.handCount[currentPlayer];i++){
        if (G.hand[currentPlayer][i] == copper || G.hand[currentPlayer][i] == silver || G.hand[currentPlayer][i] == gold){
            newNumTreasure++;
        }
    }

    // Assert two more treasure cards in hand
    if (!assertTrue(newNumTreasure == oldNumTreasure + 2,
        "Two treasure cards added"))
        testPassed = false;

	// Assert the adventurer card was discarded
	if (!assertTrue(G.playedCardCount == prevPlayedCount+1,
		"adventurer discarded after play") )
		testPassed = false;

    if (testPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
