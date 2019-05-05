/* -----------------------------------------------------------------------
 * Test for the smithy card that runs when the cardEffect function is called
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "smithy (in cardEffect)"

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

   	struct gameState G, originalG;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int handPos = 0;
    int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
    			sea_hag, tribute, smithy, adventurer};


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    G.hand[currentPlayer][handPos] = smithy;

	memcpy(&originalG, &G, sizeof(struct gameState));


	// Assert cardEffect returns 0
	if (!assertTrue(cardEffect(smithy, 0, 0, 0, &G, handPos, NULL) == 0,
	"village returns 0"))
		testPassed = false;

	// Assert state unrelated to discarding/drawing cards is unchanged
	if (!assertTrue(G.numPlayers == originalG.numPlayers,
		"numPlayers is unchanged"))
		testPassed = false;

	for (i=0;i<treasure_map+1;i++){
		if (!assertTrue(G.supplyCount[i] == originalG.supplyCount[i],
			"supply counts are unchanged"))
			testPassed = false;
	}

	if (!assertTrue(G.outpostPlayed == originalG.outpostPlayed,
		"outpostPlayed is unchanged"))
		testPassed = false;

	if (!assertTrue(G.outpostTurn == originalG.outpostTurn,
		"outpostTurn is unchanged"))
		testPassed = false;

	if (!assertTrue(G.whoseTurn == originalG.whoseTurn,
		"whoseTurn is unchanged"))
		testPassed = false;

	if (!assertTrue(G.phase == originalG.phase,
		"phase is unchanged"))
		testPassed = false;

	if (!assertTrue(G.numActions == originalG.numActions,
		"numActions is unchanged"))
		testPassed = false;

	if (!assertTrue(G.coins == originalG.coins,
		"coins is unchanged"))
		testPassed = false;

	if (!assertTrue(G.numBuys == originalG.numBuys,
		"numBuys is unchanged"))
		testPassed = false;


	// Assert the village card was discarded
	if (!assertTrue(G.playedCardCount > 0 &&
		G.playedCards[G.playedCardCount-1] == smithy,
		"smithy card in discard pile") )
		testPassed = false;

    if (testPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
