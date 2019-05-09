#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


char inputChar()
{
    // Return a random char in the set of all brackets and braces, space, a, and x
    char * possibleChars = "{}[]() ax";
    return possibleChars[rand()%9];
}

char *inputString()
{
    // Allocate a new string of length 6, set every letter to be a letter in
    // the string "reset\0"
    int i, j;
    char * newString = (char*) malloc(sizeof(char)*6);
    for (i=0;i<6;i++){
        j = rand()%5;
        if (j==0)
            newString[i] = 'r';
        else if (j==1)
            newString[i] = 'e';
        else if (j==2)
            newString[i] = 's';
        else if (j==3)
            newString[i] = 't';
        else
            newString[i] = '\0';
    }
    return newString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
