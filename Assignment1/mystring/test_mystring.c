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
  char* original;

  original = "I am testing my string functions!";
  mystrcpy(buffer, original);
  assert(strcmp(buffer, original) == 0);

  original = "Iamtestingmystringfunctions!";
  mystrcpy(buffer, original);
  assert(strcmp(buffer, original) == 0);

  original = " I am testing my string functions!";
  mystrcpy(buffer, original);
  assert(strcmp(buffer, original) == 0);

  original = "I am testing my string functions! ";
  mystrcpy(buffer, original);
  assert(strcmp(buffer, original) == 0);

  original = " I am testing my string functions! ";
  mystrcpy(buffer, original);
  assert(strcmp(buffer, original) == 0);

  original = "I am testing my string functions!\0";
  mystrcpy(buffer, original);
  assert(strcmp(buffer, original) == 0);

  original = "I am testing my \0string functions!\0";
  mystrcpy(buffer, original);
  assert(strcmp(buffer, original) == 0);

  original = "I";
  mystrcpy(buffer, original);
  assert(strcmp(buffer, original) == 0);

  /*
   * Tests for mystrcmp()
   */
	assert(mystrcmp("I love coding", "I love coding") == 0);
	assert(mystrcmp("I love codin", "I love coding") == -1);
	assert(mystrcmp("I love coding", "I love codin") == 1);
	assert(mystrcmp("app", "app") == 0);
	assert(mystrcmp("apple", "app") == 1);
	assert(mystrcmp("app", "apple") == -1);
	assert(mystrcmp("a", "b") == -1);
	assert(mystrcmp("b", "a") == 1);
	assert(mystrcmp("", "a") == -1);
	assert(mystrcmp("a", "") == 1);
	assert(mystrcmp("", "") == 0);
	assert(mystrcmp("cat", "cat") == 0);
	assert(mystrcmp("cat", "fat") == -1);
	assert(mystrcmp("fat", "cat") == 1);
	assert(mystrcmp("boat", "boat") == 0);
	assert(mystrcmp("boat", "brat") == -1);
	assert(mystrcmp("brat", "boat") == 1);
	assert(mystrcmp("play", "play") == 0);
	assert(mystrcmp("plan", "play") == -1);
	assert(mystrcmp("play", "plan") == 1);

  /*
   * Tests for mystrdup()
   */
	char *dupStr = mystrdup(buffer);
	assert (!strcmp(buffer, dupStr));
	assert (buffer != dupStr);

	if (dupStr != NULL) {
		free (dupStr);
  }

	printf ("\nPassed all tests!!!\n\n");

	return 0;
}
