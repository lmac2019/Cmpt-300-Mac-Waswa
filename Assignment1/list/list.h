#ifndef MemoryList_H
#define MemoryList_H

/* Include necessary external libraries */

#include <stdio.h>
#include <stdlib.h>

/* nodeStruct definition */

struct nodeStruct {
  int item;
  struct nodeStruct* next;
};

/* nodeStructPtr definition */

#define nodeStructPtr nodeStruct*

/* Function prototypes */

struct nodeStructPtr MemoryList_createNode (int item);
void MemoryList_insertHead (struct nodeStructPtr* headRef, struct nodeStructPtr node);
void MemoryList_insertTail (struct nodeStructPtr* headRef, struct nodeStructPtr node);
int MemoryList_countNodes (struct nodeStructPtr head);
struct nodeStructPtr MemoryList_findNode (struct nodeStructPtr head, int item);
void MemoryList_deleteNode (struct nodeStructPtr* headRef, struct nodeStructPtr node);
void MemoryList_sort (struct nodeStructPtr* headRef);

#endif