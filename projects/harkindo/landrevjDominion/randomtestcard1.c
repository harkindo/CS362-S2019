#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "council room"

int random(int low, int high){
	return (rand()%(high-low+1)) + low;
}

bool assertTrue(bool b, char * errMsg){
    if (b) {
        return true;
    }
    else {
        printf("Fail: did not assert '%s'\n", errMsg);
        return false;
    }
}

// returns location of card in hand
int randomState(struct gameState * G, int card){
	int i,j;
	G->numPlayers = random(2, MAX_PLAYERS);

	for (i=0;i<treasure_map+1;i++){
		G->supplyCount[i] = random(0, 20);
		G->embargoTokens[i] = random(0, 2);
	}

	G->outpostPlayed = random(0, 1);
	G->outpostTurn = 0;
	G->whoseTurn = random(0, G->numPlayers-1);
	G->phase = 1;
	G->numActions = random(1, 3);
	G->coins = random(0, 5);
	G->numBuys = random(1, 3);

	for (i=0;i<G->numPlayers;i++){
		G->handCount[i] = random(0, 10);
		G->deckCount[i] = random(4, MAX_DECK);
		G->discardCount[i] = 0;

		for (j=0;j< G->handCount[i];j++){
			G->hand[i][j] = random(curse, treasure_map);
		}
		for (j=0;j< G->deckCount[i];j++){
			G->deck[i][j] = random(curse, treasure_map);
		}
		for (j=0;j< G->discardCount[i];j++){
			G->discard[i][j] = random(curse, treasure_map);
		}
	}

	memset(G->playedCards, 0, MAX_DECK);
	G->playedCardCount = 0;

	// Set a card in the current player's hand to the specified card
	if (G->handCount[G->whoseTurn] == 0){
		G->handCount[G->whoseTurn] = 1;
	}
	i = random(0, G->handCount[G->whoseTurn]);
	G->hand[G->whoseTurn][i] = card;
	return i;
}

int main() {
    bool testPassed = true;

	int i, handPos, numRuns;

   	struct gameState G, originalG;

	srand(time(0));


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for (numRuns = 0; numRuns < 1000; numRuns++){
		handPos = randomState(&G, council_room);
		memcpy(&originalG, &G, sizeof(struct gameState));

		// Assert council room returns 0
		if (!assertTrue(cardEffect(council_room, 0, 0, 0, &G, handPos, NULL) == 0,
		"council room returns 0"))
			testPassed = false;

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

		if (!assertTrue(G.numBuys == originalG.numBuys + 1,
			"numBuys is incremented"))
			testPassed = false;

		for (i=0;i<G.numPlayers;i++){
			if (i != G.whoseTurn){
				if (!assertTrue(G.handCount[i] == originalG.handCount[i] + 1,
					"hand counts are increased by 1 for non-current player"))
					testPassed = false;
				if (!assertTrue(G.deckCount[i] == originalG.deckCount[i] - 1
								|| G.deckCount[i] > originalG.deckCount[i],
					"deck counts are decremented, or shuffled and greater than original for non-current player"))
					testPassed = false;
				if (!assertTrue(G.discardCount[i] == originalG.discardCount[i],
					"discard counts are unchanged for non-current player"))
					testPassed = false;
			}
			else {
				if (!assertTrue(G.handCount[i] == originalG.handCount[i] + 3,
					"hand counts are increased by 4 (and 1 card discarded) for current player"))
					testPassed = false;
				if (!assertTrue(G.deckCount[i] == originalG.deckCount[i] - 4
								|| G.deckCount[i] > originalG.deckCount[i],
					"deck counts are decremented by 4, or shuffled and greater than original for current player"))
					testPassed = false;
			}
		}

		if (!assertTrue(G.playedCardCount == originalG.playedCardCount+1,
			"played card count has changed, one card discarded"))
			testPassed = false;
	}


    if (testPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
