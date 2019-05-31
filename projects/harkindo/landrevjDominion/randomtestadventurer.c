#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "adventurer"

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
	int i,j,r1, r2;
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
		G->deckCount[i] = random(2, MAX_DECK);
		G->discardCount[i] = 0;

		for (j=0;j< G->handCount[i];j++){
			G->hand[i][j] = random(curse, treasure_map);
		}
		for (j=0;j< G->deckCount[i];j++){
			G->deck[i][j] = random(curse, treasure_map);
		}
		r1 = random(0,G->deckCount[i]);
		do {
			r2 = random(0,G->deckCount[i]);
		} while (r1 == r2);
		G->deck[i][r1] = copper;
		G->deck[i][r2] = copper;

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
	i = 0;
	G->hand[G->whoseTurn][i] = card;
	return i;
}

int main() {
    bool testPassed = true;

	int i, handPos, numRuns;
	int oldNumTreasure;
    int newNumTreasure;
	int oldTreasureSupply;

   	struct gameState G, originalG;

	srand(time(0));


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for (numRuns = 0; numRuns < 1000; numRuns++){
		oldNumTreasure = 0;
		newNumTreasure = 0;
		handPos = randomState(&G, adventurer);
		memcpy(&originalG, &G, sizeof(struct gameState));

		// Assert adventurer returns 0
		if (!assertTrue(cardeffect_adventurer(&G) == 0,
		"adventurer returns 0"))
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

		if (!assertTrue(G.numBuys == originalG.numBuys,
			"numBuys is unchanged"))
			testPassed = false;

		for (i=0;i<G.numPlayers;i++){
			if (i != G.whoseTurn){
				if (!assertTrue(G.handCount[i] == originalG.handCount[i],
					"hand counts are unchanged for non-current player"))
					testPassed = false;
				if (!assertTrue(G.deckCount[i] == originalG.deckCount[i],
					"deck counts are unchanged for non-current player"))
					testPassed = false;
				if (!assertTrue(G.discardCount[i] == originalG.discardCount[i],
					"discard counts are unchanged for non-current player"))
					testPassed = false;
			}
			else {

			}
		}

		if (!assertTrue(G.playedCardCount != originalG.playedCardCount,
			"played card count has changed, one or more cards discarded"))
			testPassed = false;


		// Get number of treasure cards initialy in hand
	    for (i=0;i<originalG.handCount[G.whoseTurn];i++){
	        if (originalG.hand[G.whoseTurn][i] == copper || originalG.hand[G.whoseTurn][i] == silver || originalG.hand[G.whoseTurn][i] == gold){
	            oldNumTreasure++;
	        }
	    }

		// Get number of treasure cards now in hand
	    for (i=0;i<G.handCount[G.whoseTurn];i++){
	        if (G.hand[G.whoseTurn][i] == copper || G.hand[G.whoseTurn][i] == silver || G.hand[G.whoseTurn][i] == gold){
	            newNumTreasure++;
	        }
	    }

		oldTreasureSupply = G.supplyCount[copper] + G.supplyCount[silver] + G.supplyCount[gold];


	    // Assert two more treasure cards in hand
	    if (!assertTrue(newNumTreasure == oldNumTreasure + 2 || oldTreasureSupply < 2,
	        "Two treasure cards added")){
	        testPassed = false;
			printf("Old num treasure:%d \nNew num treasure: %d\n Treasure supply: %d\n",oldNumTreasure, newNumTreasure, oldTreasureSupply );
		}
	}


    if (testPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
