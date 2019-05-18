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
int mystrlen (const char *s)
{
	int len = 0;
	while(s[len] != '\0'){
		len++;
	}
	return len;
}

/*
 *  mystrcpy()  copies the string pointed to by src (including the terminating
 *  character '\0') to the array pointed to by dst.
 *  Returns: a  pointer to the destination string dst.
 */
char  *mystrcpy (char *dst, const char *src)
{
	int len = 0;
	if(dst == NULL){
		return NULL;
	}
	while(src[len] != '\0'){
		dst[len] = src[len];
		len++;
	}
	dst[len] = '\0';
	return dst;
}

/*
 * mystrcmp() compares two strings alphabetically
 * Returns:
 * 	-1 if s1  < s2
 *  	0 if s1 == s2
 *  	1 if s1 > s2
 */
int mystrcmp(const char *s1, const char *s2)
{
	int len = 0;
	while(s1[len] != '\0'){
		if(s1[len] < s2[len]){
			return -1;
		}
		if(s1[len] > s2[len]){
			return 1;
		}
		len++;
	}
	return 0;
}

/*
 * mystrdup() creates a duplicate of the string pointed to by s.
 * The space for the new string is obtained using malloc.
 * If the new string can not be created, a null pointer is returned.
 * Returns:  a pointer to a new string (the duplicate)
 	     or null If the new string could not be created for
	     any reason such as insufficient memory.
 */
char *mystrdup(const char *s1)
{
	int len = mystrlen(s1);
	char *dup;
	if(len == 0){
		return NULL;
	}
	dup = (char *)malloc((len+1)*sizeof(char));
	mystrcpy(dup,s1);
	return dup;
}