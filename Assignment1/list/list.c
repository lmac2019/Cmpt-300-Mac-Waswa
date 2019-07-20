#include "list.h"

/*
 * Allocate memory for a node of type struct nodeStruct and initialize
 * it with the value item. Return a pointer to the new node.
 */
struct nodeStructPtr MemoryList_createNode (int item) {
  struct nodeStructPtr ptr = (struct nodeStructPtr) malloc(sizeof(struct nodeStruct));
  ptr->item = item;
  ptr->next = NULL;
  return ptr;
}

/*
 * Insert node at the head of the list.
 */
void MemoryList_insertHead (struct nodeStructPtr* headRef, struct nodeStructPtr node) {
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
void MemoryList_insertTail (struct nodeStructPtr* headRef, struct nodeStructPtr node) {
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
int MemoryList_countNodes (struct nodeStructPtr head) {
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
struct nodeStructPtr MemoryList_findNode (struct nodeStructPtr head, int item) {
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
 * MemoryList_findNode(). If the list contains only one node, the head of the list
 * should be set to NULL.
 */
void MemoryList_deleteNode (struct nodeStructPtr* headRef, struct nodeStructPtr node) {
  struct nodeStructPtr currentNodePtr = *headRef;
  if (*headRef == node) {
    *headRef = currentNodePtr->next;
    free(currentNodePtr);
    return;
  }

  for (currentNodePtr = *headRef; currentNodePtr != NULL && currentNodePtr->next != node; currentNodePtr = currentNodePtr->next) {
  }

  if (currentNodePtr->next == node) {
    struct nodeStructPtr tempNodePtr = node->next;
    free(currentNodePtr->next);
    currentNodePtr->next = tempNodePtr;
  }
}

 /*
  * Sort the list in ascending order based on the item field.
  * Any sorting algorithm is fine.
  */
void MemoryList_sort (struct nodeStructPtr* headRef) {
  if (*headRef == NULL) {
    return;
  }

  const int STOP_SORTING = 0;
  const int KEEP_SORTING = 1;
  struct nodeStructPtr tempNodePtr;
  struct nodeStructPtr previousNodePtr;

  int sort;
  do {
    sort = STOP_SORTING;

    for (tempNodePtr = *headRef, previousNodePtr = *headRef; tempNodePtr->next != NULL; tempNodePtr = tempNodePtr->next) {

      if ((tempNodePtr == previousNodePtr) && (tempNodePtr->item > tempNodePtr->next->item)) {

        struct nodeStructPtr afterTempNodePtrNextPtr = tempNodePtr->next->next;

        *headRef = tempNodePtr->next;
        (*headRef)->next = tempNodePtr;
        tempNodePtr->next = afterTempNodePtrNextPtr;

        previousNodePtr = *headRef;
        tempNodePtr = *headRef;

        sort = KEEP_SORTING;

      } else if (tempNodePtr->item > tempNodePtr->next->item) {

        struct nodeStructPtr currentNodePtr = tempNodePtr;
        struct nodeStructPtr afterTempNodePtrNextPtr = tempNodePtr->next->next;

        previousNodePtr->next = tempNodePtr->next;
        tempNodePtr->next->next = currentNodePtr;
        currentNodePtr->next = afterTempNodePtrNextPtr;

        tempNodePtr = previousNodePtr->next;

        sort = KEEP_SORTING;

      }

      if (tempNodePtr != *headRef) {
        previousNodePtr = previousNodePtr->next;
      }

    }
  } while (sort == KEEP_SORTING);
}