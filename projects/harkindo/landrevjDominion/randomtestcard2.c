#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "baron"

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
	int oldNumEstates, numEstates, numEstatesDiff;

	int i, handPos, numRuns, choice;

   	struct gameState G, originalG;

	srand(time(0));


    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for (numRuns = 0; numRuns < 1000; numRuns++){
		handPos = randomState(&G, council_room);
		choice = random(0, 1);
		memcpy(&originalG, &G, sizeof(struct gameState));

		// Assert baron returns 0
		if (!assertTrue(cardEffect(baron, choice, 0, 0, &G, handPos, NULL) == 0,
		"baron returns 0"))
			testPassed = false;

		if (!assertTrue(G.numPlayers == originalG.numPlayers,
			"numPlayers is unchanged"))
			testPassed = false;

		for (i=0;i<treasure_map+1;i++){
			if (!assertTrue(G.supplyCount[i] == originalG.supplyCount[i] || i == estate,
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

		/*if (!assertTrue(G.coins == originalG.coins,
			"coins is unchanged"))
			testPassed = false;*/

		if (!assertTrue(G.numBuys == originalG.numBuys + 1,
			"numBuys is incremented"))
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
		}
		oldNumEstates = 0;
		numEstates = 0;
		numEstatesDiff = 0;
		for (i=0;i<originalG.handCount[originalG.whoseTurn];i++){
			if (originalG.hand[originalG.whoseTurn][i] == estate)
				oldNumEstates++;
		}
		for (i=0;i<G.handCount[G.whoseTurn];i++){
			if (G.hand[G.whoseTurn][i] == estate)
				numEstates++;
		}
		for (i=0;i<G.discardCount[G.whoseTurn];i++){
			if (G.discard[G.whoseTurn][i] == estate)
				numEstatesDiff++;
		}
		for (i=0;i<originalG.discardCount[originalG.whoseTurn];i++){
			if (originalG.discard[originalG.whoseTurn][i] == estate)
				numEstatesDiff--;
		}
		if (oldNumEstates > 0 && choice == 1){
			if (!assertTrue(G.coins == originalG.coins + 4,
				"estate exchanged for 4 coins"))
				testPassed = false;
			if (!assertTrue(numEstates == oldNumEstates - 1,
				"1 estate removed from hand"))
				testPassed = false;
		}
		else {
			if (!assertTrue(G.supplyCount[estate] == originalG.supplyCount[estate] - 1
							|| originalG.supplyCount[estate] == 0,
				"estate removed from supply"))
				testPassed = false;
			if (!assertTrue(G.coins == originalG.coins,
				"no coins added since no estate in original hand"))
				testPassed = false;
			if (!assertTrue(numEstatesDiff == 1 || originalG.supplyCount[estate] == 0,
				"estate added to deck (or no estate in supply pile)")){
				printf("Estates diff: %d\n", numEstatesDiff);
				testPassed = false;
			}
		}

		if (!assertTrue(G.playedCardCount != originalG.playedCardCount,
			"played card count has changed, one card discarded"))
			testPassed = false;
	}


    if (testPassed)
        printf("Unit Test Passed!\n");

    return 0;
}
