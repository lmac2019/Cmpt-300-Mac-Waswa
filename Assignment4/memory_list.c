#include "memory_list.h"

/*
 * Allocate memory for a node of type struct memoryNode and initialize
 * it with the current pointing to block. Return a pointer to the new node.
 */
struct memoryNodePtr List_createNode (int block_size, voidPtr block) {
  struct memoryNodePtr ptr = (struct memoryNodePtr) malloc(sizeof(struct memoryNode));
  ptr->current = block;
  ptr->block_size = block_size;
  ptr->next = NULL;
  return ptr;
}

/*
 * Insert node at the head of the list.
 */
void List_insertHead (struct memoryNodePtr* headRef, struct memoryNodePtr node) {
  if (*headRef == NULL) {
    *headRef = node;
    return;
  }

  struct memoryNodePtr tempNodePtr = *headRef;
  *headRef = node;
  (*headRef)->next = tempNodePtr;
}

/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct memoryNodePtr* headRef, struct memoryNodePtr node) {
  if (*headRef == NULL) {
    *headRef = node;
    return;
  }

  struct memoryNodePtr currentNodePtr;
  for (currentNodePtr = *headRef; currentNodePtr->next != NULL; currentNodePtr = currentNodePtr->next) {
  }

  currentNodePtr->next = node;
}

/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes (struct memoryNodePtr head) {
  if (head == NULL) {
    return 0;
  }

  int num_nodes = 0;
  for (struct memoryNodePtr currentNodePtr = head; currentNodePtr != NULL; currentNodePtr = currentNodePtr->next) {
    num_nodes++;
  }

  return num_nodes;
}

/*
 * Return the first node holding the block, return NULL if none found
 */
struct memoryNodePtr List_findNode (struct memoryNodePtr head, voidPtr block) {
  if (head == NULL) {
    return NULL;
  }

  for (struct memoryNodePtr currentNodePtr = head; currentNodePtr != NULL; currentNodePtr = currentNodePtr->next) {
    if (currentNodePtr->current == block) {
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
void List_deleteNode (struct memoryNodePtr* headRef, struct memoryNodePtr node) {
  struct memoryNodePtr currentNodePtr = *headRef;
  if (*headRef == node) {
    *headRef = currentNodePtr->next;
    free(currentNodePtr);
    return;
  }

  for (currentNodePtr = *headRef; currentNodePtr != NULL && currentNodePtr->next != node; currentNodePtr = currentNodePtr->next) {
  }

  if (currentNodePtr->next == node) {
    struct memoryNodePtr tempNodePtr = node->next;
    free(currentNodePtr->next);
    currentNodePtr->next = tempNodePtr;
  }
}

 /*
  * Sort the list in ascending order based on the block size.
  * Any sorting algorithm is fine.
  */
void List_sort (struct memoryNodePtr* headRef) {
  if (*headRef == NULL) {
    return;
  }

  const int STOP_SORTING = 0;
  const int KEEP_SORTING = 1;
  struct memoryNodePtr tempNodePtr;
  struct memoryNodePtr previousNodePtr;

  int sort;
  do {
    sort = STOP_SORTING;

    for (tempNodePtr = *headRef, previousNodePtr = *headRef; tempNodePtr->next != NULL; tempNodePtr = tempNodePtr->next) {

      if ((tempNodePtr == previousNodePtr) && (tempNodePtr->block_size > ((struct memoryNodePtr)tempNodePtr->next)->block_size)) {

        struct memoryNodePtr afterTempNodePtrNextPtr = ((struct memoryNodePtr)tempNodePtr->next)->next;

        *headRef = tempNodePtr->next;
        (*headRef)->next = tempNodePtr;
        tempNodePtr->next = afterTempNodePtrNextPtr;

        previousNodePtr = *headRef;
        tempNodePtr = *headRef;

        sort = KEEP_SORTING;

      } else if (tempNodePtr->block_size > ((struct memoryNodePtr)tempNodePtr->next)->block_size) {

        struct memoryNodePtr currentNodePtr = tempNodePtr;
        struct memoryNodePtr afterTempNodePtrNextPtr = ((struct memoryNodePtr)tempNodePtr->next)->next;

        previousNodePtr->next = tempNodePtr->next;
        ((struct memoryNodePtr)tempNodePtr->next)->next = currentNodePtr;
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