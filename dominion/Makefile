CFLAGS= -Wall -fpic -coverage -lm -std=c99

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	> unittestresults.out

	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 councilRoomEffect >> unittestresults.out
	gcov -abc dominion.c | grep -A 4 File >> unittestresults.out

	echo "" >> unittestresults.out

	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 mineEffect >> unittestresults.out
	gcov -abc dominion.c | grep -A 4 File >> unittestresults.out

	echo "" >> unittestresults.out

	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 smithyEffect >> unittestresults.out
	gcov -abc dominion.c | grep -A 4 File >> unittestresults.out

	echo "" >> unittestresults.out

	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 baronEffect >> unittestresults.out
	gcov -abc dominion.c | grep -A 4 File >> unittestresults.out

	echo "" >> unittestresults.out

	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 cardEffect >> unittestresults.out
	gcov -abc dominion.c | grep -A 4 File >> unittestresults.out

	echo "" >> unittestresults.out

	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 cardEffect >> unittestresults.out
	gcov -abc dominion.c | grep -A 4 File >> unittestresults.out

	echo "" >> unittestresults.out

	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 cardEffect >> unittestresults.out
	gcov -abc dominion.c | grep -A 4 File >> unittestresults.out

	echo "" >> unittestresults.out

	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 cardEffect >> unittestresults.out
	gcov -abc dominion.c | grep -A 4 File >> unittestresults.out


cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 cardEffect >> unittestresults.out
	gcov -abc dominion.c >> unittestresults.out

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 cardEffect >> unittestresults.out
	gcov -abc dominion.c >> unittestresults.out

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 cardEffect >> unittestresults.out
	gcov -abc dominion.c >> unittestresults.out

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 cardEffect >> unittestresults.out
	gcov -abc dominion.c >> unittestresults.out

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 baronEffect >> unittestresults.out
	gcov -abc dominion.c >> unittestresults.out

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 smithyEffect >> unittestresults.out
	gcov -abc dominion.c >> unittestresults.out

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 mineEffect >> unittestresults.out
	gcov -abc dominion.c >> unittestresults.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -bcf dominion.c | grep -A 2 councilRoomEffect >> unittestresults.out
	gcov -abc dominion.c >> unittestresults.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
