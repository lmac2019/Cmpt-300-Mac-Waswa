#include "mystring.h"
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The following are simple tests to help you.
 * You should develop more extensive tests to try and find bugs.
 */
int main () {
  /*
   * Tests for mystrlen()
   */
  assert(mystrlen("cmpt 300") == 8);
	assert(mystrlen("\0") == 0);
	assert(mystrlen("c\0") == 1);
	assert(mystrlen(" c\0") == 2);
	assert(mystrlen("c \0") == 2);
	assert(mystrlen("c\0 ") == 1);
	assert(mystrlen(" c\0 ") == 2);
	assert(mystrlen("") == 0);
	assert(mystrlen(" ") == 1);
	assert(mystrlen("c") == 1);
	assert(mystrlen("c ") == 2);
	assert(mystrlen(" c") == 2);
	assert(mystrlen(" c ") == 3);
	assert(mystrlen("cmpt ") == 5);
	assert(mystrlen(" cmpt") == 5);
	assert(mystrlen(" cmpt ") == 6);
	assert(mystrlen("cmpt") == 4);

  /*
   * Tests for mystrcpy()
   */
  const int SIZE = 100;
  char buffer[SIZE];
  mystrcpy(buffer, "I am testing my string functions!");
  assert(strcmp(buffer, "I am testing my string functions!") == 0);
  
  char* original;

  original = "cmpt300";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "\0";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "c\0";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = " c\0";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "c \0";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "c\0 ";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = " c\0 ";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = " ";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "c";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "c ";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = " c";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = " c ";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "cmpt ";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = " cmpt";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = " cmpt ";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  original = "cmpt";
  char copy[strlen(original)];
  mystrcpy(copy, original);
  assert(strcmp(copy, original) == 0);

  /*
   * Tests for mystrcmp()
   */
	assert(mystrcmp("I love coding", "I love coding") == 0);

  /*
   * Tests for mystrdup()
   */
	char *dupStr = mystrdup(buffer);
	assert (!strcmp(buffer, dupStr));
	assert (buffer != dupStr);

	if (dupStr != NULL) {
		free (dupStr);
  }

	printf ("\nPassed all tests!!!\n");

	return 0;
}
