CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	-./testme
	gcov -bcf testme.c | grep testme -A 4

clean:
	-rm testme
