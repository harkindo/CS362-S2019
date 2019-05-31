/* -----------------------------------------------------------------------
 * Unit test for the councilRoomEffect function which handles when a \
 * council_room card is played.
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

   	struct gameState G, testG;
    int i;
    int seed = 1000;
    int numPlayers = 3;
    int currentPlayer = 0;
    int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
    			sea_hag, tribute, smithy, adventurer};
    int prevHandCount[MAX_PLAYERS];
    int prevPlayedCount;


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));

    // Store prevHandCount and prevPlayedCount
    for (i=0;i<numPlayers;i++){
        prevHandCount[i] = testG.handCount[i];
    }
    prevPlayedCount = testG.playedCardCount;

    councilRoomEffect(council_room, &testG, currentPlayer);

    // Assert each player gets the proper number of cards
    for (i=0;i<numPlayers;i++){
        if (i != currentPlayer){
            if (!assertTrue(prevHandCount[i] == testG.handCount[i]-1,
                "non-current players get +1 card"))
                unitTestPassed = false;
        }
        else {
            if (!assertTrue(prevHandCount[i] == testG.handCount[i] - 3,
                "current player gets +4 cards (then discards 1 card)"))
                unitTestPassed = false;
        }
    }

    // Assert the council_room card was discarded
    if (!assertTrue(testG.playedCardCount == prevPlayedCount+1,
        "council_room discarded after play") )
        unitTestPassed = false;

    // Make the council room card the first card in the second player deck, have them play it.
    currentPlayer = 1;
    testG.whoseTurn = currentPlayer;
    testG.handCount[currentPlayer] = 1;
    testG.hand[currentPlayer][0] = council_room;

    // Store prevHandCount and prevPlayedCount
    for (i=0;i<numPlayers;i++){
        prevHandCount[i] = testG.handCount[i];
    }
    prevPlayedCount = testG.playedCardCount;

    councilRoomEffect(council_room, &testG, currentPlayer);

    // Assert each player gets the proper number of cards
    for (i=0;i<numPlayers;i++){
        if (i != currentPlayer){
            if (!assertTrue(prevHandCount[i] == testG.handCount[i]-1,
                "non-current players get +1 card"))
                unitTestPassed = false;
        }
        else {
            if (!assertTrue(prevHandCount[i] == testG.handCount[i] - 3,
                "current player gets +4 cards (then discards 1 card)"))
                unitTestPassed = false;
        }
    }

    // Assert the council_room card was discarded
    if (!assertTrue(testG.playedCardCount == prevPlayedCount+1,
        "council_room discarded after play") )
        unitTestPassed = false;

    if (unitTestPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
