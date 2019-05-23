#ifndef MYSTRING_H   
#define MYSTRING_H

/* Include neccessary external libraries */

#include <stdlib.h>

/* charPtr definition */

#define charPtr char*

/* Function prototypes */

int   mystrlen (const charPtr s);
charPtr mystrcpy (charPtr dst, const  charPtr src);
int   mystrcmp (const charPtr s1, const charPtr s2);
charPtr mystrdup (const charPtr src);

#endif