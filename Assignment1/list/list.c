#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Allocate memory for a node of type struct nodeStruct and initialize
 * it with the value item. Return a pointer to the new node.
 */
struct nodeStructPtr List_createNode (int item) {
  struct nodeStructPtr ptr = (struct nodeStructPtr) malloc(sizeof(struct nodeStruct));
  ptr->item = item;
  ptr->next = NULL;
  return ptr;
}

/*
 * Insert node at the head of the list.
 */
void List_insertHead (struct nodeStructPtr* headRef, struct nodeStructPtr node) {
  if (*headRef == NULL) {
    *headRef = node;
    return;
  }

  struct nodeStructPtr tempPtr = *headRef;
  *headRef = node;
  (*headRef)->next = tempPtr;
}

void List_insertTail (struct nodeStructPtr* headRef, struct nodeStructPtr node) {

}

// int List_countNodes (struct nodeStructPtr head) {

// }

// struct nodeStructPtr List_findNode (struct nodeStructPtr head, int item) {

// }

void List_deleteNode (struct nodeStructPtr* headRef, struct nodeStructPtr node) {

}

void List_sort (struct nodeStructPtr* headRef) {

}
