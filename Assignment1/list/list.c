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

  struct nodeStructPtr tempNodePtr = *headRef;
  *headRef = node;
  (*headRef)->next = tempNodePtr;
}

/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct nodeStructPtr* headRef, struct nodeStructPtr node) {
  if (*headRef == NULL) {
    *headRef = node;
    return;
  }

  struct nodeStructPtr currentNodePtr;
  for (currentNodePtr = *headRef; currentNodePtr->next != NULL; currentNodePtr = currentNodePtr->next) {
  }

  currentNodePtr->next = node;
}

/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes (struct nodeStructPtr head) {
  if (head == NULL) {
    return 0;
  }

  int num_nodes = 0;
  for (struct nodeStructPtr currentNodePtr = head; currentNodePtr != NULL; currentNodePtr = currentNodePtr->next) {
    num_nodes++;
  }

  return num_nodes;
}

/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStructPtr List_findNode (struct nodeStructPtr head, int item) {
  if (head == NULL) {
    return NULL;
  }

  for (struct nodeStructPtr currentNodePtr = head; currentNodePtr != NULL; currentNodePtr = currentNodePtr->next) {
    if (currentNodePtr->item == item) {
      return currentNodePtr;
    }
  }

  return NULL;
}

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node
 * in the list. For example, the client code may have found it by calling
 * List_findNode(). If the list contains only one node, the head of the list
 * should be set to NULL.
 */
 void List_deleteNode (struct nodeStructPtr* headRef, struct nodeStructPtr node) {
   struct nodeStructPtr currentNodePtr = *headRef;
   if (*headRef == node) {
     *headRef = currentNodePtr->next;
     free(currentNodePtr);
     return;
   }

   for (currentNodePtr = *headRef; currentNodePtr != NULL; currentNodePtr = currentNodePtr->next) {
     if (currentNodePtr->next == node) {
       currentNodePtr->next = currentNodePtr->next->next;
       free(currentNodePtr->next);
     }
   }
 }

 /*
  * Sort the list in ascending order based on the item field.
  * Any sorting algorithm is fine.
  */
 void List_sort (struct nodeStructPtr* headRef) {
   struct nodeStructPtr temp = *headRef;
   int swap;
   int bubble = 1;
   while(bubble){
   bubble = 0;
   for (temp = *headRef; temp->next != NULL; temp = temp->next) {
   if(temp->item > temp->next->item){
   swap = temp->item;
   temp->item = temp->next->item;
   temp->next->item = swap;
   bubble = 1;
   }
   }
 }

 }
