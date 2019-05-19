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

/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct nodeStructPtr* headRef, struct nodeStructPtr node) {
  if (*headRef == NULL) {
    *headRef = node;
    return;
  }

  struct nodeStructPtr current;
  for (current = *headRef; current->next != NULL; current = current->next) {
  }

  current->next = node;
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
  for (struct nodeStructPtr current = head; current != NULL; current = current->next) {
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

  for (struct nodeStructPtr current = head; current != NULL; current = current->next) {
    if (current->item == item) {
      return current;
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
  struct nodeStructPtr current;
  for (current = head; current->next != node; current = current->next) {
  }

  struct nodeStructPtr tempPtr = current->next->next;
  free (current->next);
  current->next = tempPtr;
}

void List_sort (struct nodeStructPtr* headRef) {

}
