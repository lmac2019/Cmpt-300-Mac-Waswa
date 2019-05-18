#ifndef LIST_H
#define LIST_H

/* nodeStruct definition */

struct nodeStruct {
  int item;
  struct nodeStruct* next;
};

/* nodeStructPtr definition */

#define nodeStructPtr nodeStruct*

/* Function prototypes */

struct nodeStructPtr List_createNode (int item);
void List_insertHead (struct nodeStructPtr* headRef, struct nodeStructPtr node);
void List_insertTail (struct nodeStructPtr* headRef, struct nodeStructPtr node);
int List_countNodes (struct nodeStructPtr head);
struct nodeStructPtr List_findNode (struct nodeStructPtr head, int item);
void List_deleteNode (struct nodeStructPtr* headRef, struct nodeStructPtr node);
void List_sort (struct nodeStructPtr* headRef);

#endif