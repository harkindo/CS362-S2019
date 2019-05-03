/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "council room"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

bool assertTrue(bool b, char * errMsg){
    if (b) {
        return true;
    }
    else {
        printf("Error: did not assert '%s'\n", errMsg);
        return false;
    }
}

int main() {
    bool unitTestPassed = true;

    //int i, j, m;
    //int remove1, remove2;


   	struct gameState G, testG;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
    			sea_hag, tribute, smithy, adventurer};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    memcpy(&testG, &G, sizeof(struct gameState));

    councilRoomEffect(council_room, &testG, 0);
    int currentPlayer = whoseTurn(&testG);
    if (!assertTrue(testG.discardCount[currentPlayer] == 1, "1 card discarded") )
        unitTestPassed = false;

    if (unitTestPassed)
        printf("Unit Test Passed!\n");
}
