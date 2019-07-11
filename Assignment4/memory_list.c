#include "memory_list.h"

/*
 * Allocate memory for a node of type struct memoryNode and initialize
 * it with the current pointing to block. Return a pointer to the new node.
 */
struct memoryNodePtr MemoryList_createNode (int block_size, voidPtr block) {
  struct memoryNodePtr ptr = (struct memoryNodePtr) malloc(sizeof(struct memoryNode));
  ptr->current = block;
  ptr->block_size = block_size;
  ptr->next = NULL;
  return ptr;
}

/*
 * Insert node at the head of the list.
 */
void MemoryList_insertHead (struct memoryNodePtr* headRef, struct memoryNodePtr node) {
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
void MemoryList_insertTail (struct memoryNodePtr* headRef, struct memoryNodePtr node) {
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
int MemoryList_countNodes (struct memoryNodePtr head) {
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
struct memoryNodePtr MemoryList_findNode (struct memoryNodePtr head, voidPtr block) {
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
 * MemoryList_findNode(). If the list contains only one node, the head of the list
 * should be set to NULL.
 */
void MemoryList_deleteNode (struct memoryNodePtr* headRef, struct memoryNodePtr node) {
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
 * Deletes all nodes from the list and free memory allocated to them.
 */
void MemoryList_deleteAllNodes (struct memoryNodePtr* headRef) {
  if (*headRef == NULL) {
    return;
  }

  do {
    MemoryList_deleteNode(headRef, *headRef);
  } while (*headRef != NULL);
}

 /*
  * Sort the list in ascending order based on the block size.
  * Any sorting algorithm is fine.
  */
void MemoryList_sort (struct memoryNodePtr* headRef) {
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

      if ((tempNodePtr == previousNodePtr) && (tempNodePtr->current > ((struct memoryNodePtr)tempNodePtr->next)->current)) {

        struct memoryNodePtr afterTempNodePtrNextPtr = ((struct memoryNodePtr)tempNodePtr->next)->next;

        *headRef = tempNodePtr->next;
        (*headRef)->next = tempNodePtr;
        tempNodePtr->next = afterTempNodePtrNextPtr;

        previousNodePtr = *headRef;
        tempNodePtr = *headRef;

        sort = KEEP_SORTING;

      } else if (tempNodePtr->current > ((struct memoryNodePtr)tempNodePtr->next)->current) {

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

/*
  * Returns the smallest block size in the list
  * If no nodes then will return 0
  */
int MemoryList_findSmallestBlockSize(struct memoryNodePtr head) {
  int smallest_block_size = 0;

  for (struct memoryNodePtr currentNodePtr = head; currentNodePtr != NULL; currentNodePtr = currentNodePtr->next) {
    if (currentNodePtr == head) {
      smallest_block_size = currentNodePtr->block_size;
      continue;
    }

    if (currentNodePtr->block_size < smallest_block_size) {
      smallest_block_size = currentNodePtr->block_size;
    }
  }

  return smallest_block_size;
}

/*
  * Returns the largest block size in the list
  * If no nodes then will return 0
  */
int MemoryList_findLargestBlockSize(struct memoryNodePtr head) {
  int largest_block_size = 0;

  for (struct memoryNodePtr currentNodePtr = head; currentNodePtr != NULL; currentNodePtr = currentNodePtr->next) {
    if (currentNodePtr->block_size > largest_block_size) {
      largest_block_size = currentNodePtr->block_size;
    }
  }

  return largest_block_size;
}