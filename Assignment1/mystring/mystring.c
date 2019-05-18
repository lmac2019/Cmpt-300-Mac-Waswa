#include "mystring.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *   Implement the following functions:
 *
 *   You are NOT allowed to use any standard string functions such as
 *   strlen, strcpy or strcmp or any other string function.
 */

/*
 *  mystrlen() calculates the length of the string s,
 *  not including the terminating character '\0'.
 *  Returns: length of s.
 */
int mystrlen (const char* s) {
	int len = 0;

	while (s[len] != '\0') {
		len++;
	}

	return len;
}

/*
 *  mystrcpy()  copies the string pointed to by src (including the terminating
 *  character '\0') to the array pointed to by dst.
 *  Returns: a  pointer to the destination string dst.
 */
char* mystrcpy (char* dst, const char* src) {
	if (dst == NULL) {
		return NULL;
	}

	for (int len = 0; src[len] != '\0'; len++) {
		dst[len] = src[len];
	}

	dst[mystrlen(src)] = '\0';

	return dst;
}

/*
 * mystrcmp() compares two strings alphabetically
 * Returns:
 * 	-1 if s1  < s2
 *  	0 if s1 == s2
 *  	1 if s1 > s2
 */
int mystrcmp (const char* s1, const char* s2) {
  for (int len = 0; s1[len] != '\0' && s2[len] != '\0'; len++) {
    if (s1[len] < s2[len]) {
			return -1;
		}

		if (s1[len] > s2[len]) {
			return 1;
		}
	}

  if (mystrlen(s1) < mystrlen(s2)) {
    return -1;
  } else if (mystrlen(s1) > mystrlen(s2)) {
    return 1;
  }

	return 0;
}

/*
 * mystrdup() creates a duplicate of the string pointed to by s.
 * The space for the new string is obtained using malloc.
 * If the new string can not be created, a null pointer is returned.
 * Returns:  a pointer to a new string (the duplicate)
 * or null If the new string could not be created for
 * any reason such as insufficient memory.
 */
char* mystrdup (const char* s1) {
	int len = mystrlen(s1);
	if (len == 0) {
		return NULL;
	}

	char* duplicate = (char*) malloc((len + 1) * sizeof(char));
	mystrcpy(duplicate, s1);

	return duplicate;
}