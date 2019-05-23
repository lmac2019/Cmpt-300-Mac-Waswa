#include "list.h"

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

  for (currentNodePtr = *headRef; currentNodePtr != NULL && currentNodePtr->next != node; currentNodePtr = currentNodePtr->next) {
  }

  if (currentNodePtr->next == node) {
    struct nodeStructPtr tempNodePtr = node;
    currentNodePtr->next = node->next;
    free(tempNodePtr);
  }
}

 /*
  * Sort the list in ascending order based on the item field.
  * Any sorting algorithm is fine.
  */
void List_sort (struct nodeStructPtr* headRef) {
  if (*headRef == NULL) {
    return;
  }

  const int STOP_SORTING = 0;
  const int KEEP_SORTING = 1;

  int sort;
  do {
    sort = STOP_SORTING;

    for (struct nodeStructPtr tempNodePtr = *headRef; tempNodePtr->next != NULL; tempNodePtr = tempNodePtr->next) {
      if (tempNodePtr->item > tempNodePtr->next->item) {
        int tempNodeItem;
        tempNodeItem = tempNodePtr->item;
        tempNodePtr->item = tempNodePtr->next->item;
        tempNodePtr->next->item = tempNodeItem;
        sort = KEEP_SORTING;
      }
    }
  } while (sort == KEEP_SORTING);
}