#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>

int main (int argc, char **argv) {
  printf("Starting tests for list...\n");

  /*
   * Tests for MemoryList_createNode
   */
  struct nodeStructPtr createdNode;

  createdNode = MemoryList_createNode(-100);
  assert(createdNode->item == -100);

  // * Free memory for createdNode
  free(createdNode);

  createdNode = MemoryList_createNode(0);
  assert(createdNode->item == 0);

  // * Free memory for createdNode
  free(createdNode);

  createdNode = MemoryList_createNode(3);
  assert(createdNode->item == 3);

  // * Free memory for createdNode
  free(createdNode);

  createdNode = MemoryList_createNode(100);
  assert(createdNode->item == 100);

  // * Free memory for createdNode
  free(createdNode);

  /*
   * Tests for MemoryList_insertHead
   */
  struct nodeStructPtr head = NULL;
  struct nodeStructPtr firstNodePtr = MemoryList_createNode(22);
  struct nodeStructPtr secondNodePtr = MemoryList_createNode(132);
  struct nodeStructPtr thirdNodePtr = MemoryList_createNode(43);
  struct nodeStructPtr fourthNodePtr = MemoryList_createNode(-123);
  struct nodeStructPtr fifthNodePtr = MemoryList_createNode(-234);

  // * No nodes added to linked list
  assert(head == NULL);

  // * firstNodePtr added to head of linked list
  MemoryList_insertHead(&head, firstNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * secondNodePtr added to head of linked list
  MemoryList_insertHead(&head, secondNodePtr);
  assert(head == secondNodePtr);
  assert(secondNodePtr->next == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * thirdNodePtr, fourthNodePtr and fifthNodePtr added to head of linked list sequentially
  MemoryList_insertHead(&head, thirdNodePtr);
  MemoryList_insertHead(&head, fourthNodePtr);
  MemoryList_insertHead(&head, fifthNodePtr);
  assert(head == fifthNodePtr);
  assert(fifthNodePtr->next == fourthNodePtr);
  assert(fourthNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * Free memory for firstNodePtr, secondNodePtr, thirdNodePtr, fourthNodePtr and fifthNodePtr
  free(firstNodePtr);
  free(secondNodePtr);
  free(thirdNodePtr);
  free(fourthNodePtr);
  free(fifthNodePtr);

  /*
   * Tests for MemoryList_insertTail
   */
  head = NULL;
  firstNodePtr = MemoryList_createNode(22);
  secondNodePtr = MemoryList_createNode(132);
  thirdNodePtr = MemoryList_createNode(43);
  fourthNodePtr = MemoryList_createNode(-123);
  fifthNodePtr = MemoryList_createNode(-234);

  // * No nodes added to linked list
  assert(head == NULL);

  // * firstNodePtr added to tail of linked list
  MemoryList_insertTail(&head, firstNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * secondNodePtr added to tail of linked list
  MemoryList_insertTail(&head, secondNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == NULL);

  // * thirdNodePtr, fourthNodePtr, fifthNodePtr added to tail of linked list sequentially
  MemoryList_insertTail(&head, thirdNodePtr);
  MemoryList_insertTail(&head, fourthNodePtr);
  MemoryList_insertTail(&head, fifthNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == fourthNodePtr);
  assert(fourthNodePtr->next == fifthNodePtr);
  assert(fifthNodePtr->next == NULL);

  // * Free memory for firstNodePtr, secondNodePtr, thirdNodePtr, fourthNodePtr and fifthNodePtr
  free(fifthNodePtr);
  free(fourthNodePtr);
  free(thirdNodePtr);
  free(secondNodePtr);
  free(firstNodePtr);

  /*
   * Tests for MemoryList_countNodes
   */
  head = NULL;
  firstNodePtr = MemoryList_createNode(22);
  secondNodePtr = MemoryList_createNode(132);
  thirdNodePtr = MemoryList_createNode(43);
  fourthNodePtr = MemoryList_createNode(-123);
  fifthNodePtr = MemoryList_createNode(-234);

  // * No nodes added to linked list
  assert(MemoryList_countNodes(head) == 0);

  // * One node added to linked list (added to tail)
  MemoryList_insertTail(&head, firstNodePtr);
  assert(MemoryList_countNodes(head) == 1);

  // * Free memory for firstNodePtr
  free(firstNodePtr);

  head = NULL;
  firstNodePtr = MemoryList_createNode(22);

  // * One node added to linked list (added to head)
  MemoryList_insertHead(&head, firstNodePtr);
  assert(MemoryList_countNodes(head) == 1);

  // * Two nodes added to linked list (added to head)
  MemoryList_insertHead(&head, secondNodePtr);
  assert(MemoryList_countNodes(head) == 2);

  // * Free memory for firstNodePtr and secondNodePtr
  free(firstNodePtr);
  free(secondNodePtr);

  head = NULL;
  firstNodePtr = MemoryList_createNode(22);
  secondNodePtr = MemoryList_createNode(132);

  // * Two nodes added to linked list (added to tail)
  MemoryList_insertTail(&head, firstNodePtr);
  MemoryList_insertTail(&head, secondNodePtr);
  assert(MemoryList_countNodes(head) == 2);

  // * Free memory for secondNodePtr and firstNodePtr
  free(secondNodePtr);
  free(firstNodePtr);

  head = NULL;
  firstNodePtr = MemoryList_createNode(22);
  secondNodePtr = MemoryList_createNode(132);

  // * Two nodes added to linked list (first one added to tail, second one added to head)
  MemoryList_insertTail(&head, firstNodePtr);
  MemoryList_insertHead(&head, secondNodePtr);
  assert(MemoryList_countNodes(head) == 2);

  // * Free memory for firstNodePtr and secondNodePtr
  free(firstNodePtr);
  free(secondNodePtr);

  head = NULL;
  firstNodePtr = MemoryList_createNode(22);
  secondNodePtr = MemoryList_createNode(132);

  // * Two nodes added to linked list (first one added to head, second one added to tail)
  MemoryList_insertHead(&head, firstNodePtr);
  MemoryList_insertTail(&head, secondNodePtr);
  assert(MemoryList_countNodes(head) == 2);

  // * Free memory for secondNodePtr and firstNodePtr
  free(secondNodePtr);
  free(firstNodePtr);

  head = NULL;

  // * Three nodes added to linked list (added to tail)
  MemoryList_insertTail(&head, thirdNodePtr);
  MemoryList_insertTail(&head, fourthNodePtr);
  MemoryList_insertTail(&head, fifthNodePtr);
  assert(MemoryList_countNodes(head) == 3);

  // * Free memory for fifthNodePtr, fourthNodePtr and thirdNodePtr
  free(fifthNodePtr);
  free(fourthNodePtr);
  free(thirdNodePtr);

  /*
   * Tests for MemoryList_findNode
   */
  head = NULL;
  firstNodePtr = MemoryList_createNode(22);
  secondNodePtr = MemoryList_createNode(132);
  thirdNodePtr = MemoryList_createNode(43);
  fourthNodePtr = MemoryList_createNode(-123);
  fifthNodePtr = MemoryList_createNode(-456);

  // * Four nodes added sequentially to the tail
  MemoryList_insertTail(&head, firstNodePtr);
  MemoryList_insertTail(&head, secondNodePtr);
  MemoryList_insertTail(&head, thirdNodePtr);
  MemoryList_insertTail(&head, fourthNodePtr);
  assert(MemoryList_findNode(head, firstNodePtr->item) == firstNodePtr);
  assert(MemoryList_findNode(head, secondNodePtr->item) == secondNodePtr);
  assert(MemoryList_findNode(head, thirdNodePtr->item) == thirdNodePtr);
  assert(MemoryList_findNode(head, fourthNodePtr->item) == fourthNodePtr);
  assert(MemoryList_findNode(head, fifthNodePtr->item) == NULL);

  // * Free memory for fifthNodePtr, fourthNodePtr, thirdNodePtr, secondNodePtr and firstNodePtr
  free(fifthNodePtr);
  free(fourthNodePtr);
  free(thirdNodePtr);
  free(secondNodePtr);
  free(firstNodePtr);

  /*
   * Tests for MemoryList_deleteNode
   */
  head = NULL;
  firstNodePtr = MemoryList_createNode(22);
  secondNodePtr = MemoryList_createNode(132);
  thirdNodePtr = MemoryList_createNode(43);

  // * Remove first node in a linked list with one node (added to the tail)
  int itemToBeRemoved = firstNodePtr->item;
  MemoryList_insertTail(&head, firstNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);
  assert(MemoryList_findNode(head, itemToBeRemoved) == NULL);
  assert(head == NULL);

  // * Remove first node in a linked list with one node (added to the head)
  firstNodePtr = MemoryList_createNode(100);
  itemToBeRemoved = firstNodePtr->item;
  MemoryList_insertHead(&head, firstNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);
  assert(MemoryList_findNode(head, itemToBeRemoved) == NULL);
  assert(head == NULL);

  // * Remove first node in a linked list with two nodes
  firstNodePtr = MemoryList_createNode(102);
  itemToBeRemoved = firstNodePtr->item;
  MemoryList_insertTail(&head, firstNodePtr);
  MemoryList_insertTail(&head, secondNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);
  assert(MemoryList_findNode(head, itemToBeRemoved) == NULL);
  assert(MemoryList_findNode(head, secondNodePtr->item) == secondNodePtr);
  assert(head == secondNodePtr);
  assert(secondNodePtr->next == NULL);

  // * Remove last node in a linked list with two nodes
  firstNodePtr = MemoryList_createNode(111);
  itemToBeRemoved = secondNodePtr->item;
  MemoryList_insertHead(&head, firstNodePtr);
  MemoryList_deleteNode(&head, secondNodePtr);
  assert(MemoryList_findNode(head, firstNodePtr->item) == firstNodePtr);
  assert(MemoryList_findNode(head, itemToBeRemoved) == NULL);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * Remove first node in a linked list with three nodes
  itemToBeRemoved = firstNodePtr->item;
  secondNodePtr = MemoryList_createNode(32);
  MemoryList_insertTail(&head, secondNodePtr);
  MemoryList_insertTail(&head, thirdNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);
  assert(MemoryList_findNode(head, itemToBeRemoved) == NULL);
  assert(MemoryList_findNode(head, secondNodePtr->item) == secondNodePtr);
  assert(MemoryList_findNode(head, thirdNodePtr->item) == thirdNodePtr);
  assert(head == secondNodePtr);
  assert(head->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Remove middle node in a linked list with three nodes
  itemToBeRemoved = secondNodePtr->item;
  firstNodePtr = MemoryList_createNode(19);
  MemoryList_insertHead(&head, firstNodePtr);
  MemoryList_deleteNode(&head, secondNodePtr);
  assert(MemoryList_findNode(head, firstNodePtr->item) == firstNodePtr);
  assert(MemoryList_findNode(head, itemToBeRemoved) == NULL);
  assert(MemoryList_findNode(head, thirdNodePtr->item) == thirdNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Remove last node in a linked list with three nodes
  secondNodePtr = MemoryList_createNode(119);
  itemToBeRemoved = secondNodePtr->item;
  MemoryList_insertTail(&head, secondNodePtr);
  MemoryList_deleteNode(&head, secondNodePtr);
  assert(MemoryList_findNode(head, firstNodePtr->item) == firstNodePtr);
  assert(MemoryList_findNode(head, thirdNodePtr->item) == thirdNodePtr);
  assert(MemoryList_findNode(head, itemToBeRemoved) == NULL);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Free memory for secondNodePtr and thirdNodePtr
  free(thirdNodePtr);
  free(firstNodePtr);

  /*
  * Tests for MemoryList_sort
  */
  head = NULL;
  firstNodePtr = MemoryList_createNode(22);
  secondNodePtr = MemoryList_createNode(132);
  thirdNodePtr = MemoryList_createNode(43);

  // * Sorting an empty list
  MemoryList_sort(&head);
  assert(head == NULL);

  // * Sorting a list with one entry (added to the head)
  MemoryList_insertHead(&head, firstNodePtr);
  MemoryList_sort(&head);
  assert(head == firstNodePtr);
  assert(head->item == 22);
  assert(head->next == NULL);

  // * Free memory for firstNodePtr
  MemoryList_deleteNode(&head, firstNodePtr);

  // * Sorting a list with one entry (added to the tail)
  firstNodePtr = MemoryList_createNode(2);
  MemoryList_insertTail(&head, firstNodePtr);
  MemoryList_sort(&head);
  assert(head == firstNodePtr);
  assert(head->item == 2);
  assert(head->next == NULL);

  // * Sorting a list with two entries (originally unsorted)
  MemoryList_insertHead(&head, secondNodePtr);
  MemoryList_sort(&head);
  assert(head == firstNodePtr);
  assert(head->item == 2);
  assert(head->next == secondNodePtr);
  assert(head->next->item == 132);
  assert(head->next->next == NULL);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == NULL);

  // * Free memory for secondNodePtr
  MemoryList_deleteNode(&head, secondNodePtr);

  // * Sorting a list with two entries (originally sorted with different item values)
  secondNodePtr = MemoryList_createNode(100);
  MemoryList_insertTail(&head, secondNodePtr);
  MemoryList_sort(&head);
  assert(head == firstNodePtr);
  assert(head->item == 2);
  assert(head->next == secondNodePtr);
  assert(head->next->item == 100);
  assert(head->next->next == NULL);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == NULL);

  // * Free memory for secondNodePtr and firstNodePtr
  MemoryList_deleteNode(&head, secondNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);

  // * Sorting a list with two entries (originally sorted with the same item values)
  firstNodePtr = MemoryList_createNode(7);
  MemoryList_insertTail(&head, firstNodePtr);
  secondNodePtr = MemoryList_createNode(7);
  MemoryList_insertTail(&head, secondNodePtr);
  MemoryList_sort(&head);
  assert(head == firstNodePtr);
  assert(head->item == 7);
  assert(head->next == secondNodePtr);
  assert(head->next->item == 7);
  assert(head->next->next == NULL);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == NULL);

  // * Free memory for secondNodePtr and firstNodePtr
  MemoryList_deleteNode(&head, secondNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);

  // * Sorting a list with three entries (smallest at the front and largest at the end)
  firstNodePtr = MemoryList_createNode(-20);
  MemoryList_insertHead(&head, firstNodePtr);
  secondNodePtr = MemoryList_createNode(10);
  MemoryList_insertTail(&head, secondNodePtr);
  MemoryList_insertTail(&head, thirdNodePtr);
  MemoryList_sort(&head);
  assert(head == firstNodePtr);
  assert(head->item == -20);
  assert(head->next == secondNodePtr);
  assert(head->next->item == 10);
  assert(head->next->next == thirdNodePtr);
  assert(head->next->next->item == 43);
  assert(head->next->next->next == NULL);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Free memory for secondNodePtr and firstNodePtr
  MemoryList_deleteNode(&head, secondNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);

  // * Sorting a list with three entries (largest at the front and smallest at the end)
  firstNodePtr = MemoryList_createNode(1);
  MemoryList_insertTail(&head, firstNodePtr);
  secondNodePtr = MemoryList_createNode(-20);
  MemoryList_insertTail(&head, secondNodePtr);
  MemoryList_sort(&head);
  assert(head == secondNodePtr);
  assert(head->item == -20);
  assert(head->next == firstNodePtr);
  assert(head->next->item == 1);
  assert(head->next->next == thirdNodePtr);
  assert(head->next->next->item == 43);
  assert(head->next->next->next == NULL);
  assert(secondNodePtr->next == firstNodePtr);
  assert(firstNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Free memory for firstNodePtr, secondNodePtr and thirdNodePtr
  MemoryList_deleteNode(&head, thirdNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);
  MemoryList_deleteNode(&head, secondNodePtr);

  // * Sorting a list with four entries (smallest at the front and largest at the end)
  firstNodePtr = MemoryList_createNode(0);
  MemoryList_insertHead(&head, firstNodePtr);
  secondNodePtr = MemoryList_createNode(5);
  MemoryList_insertTail(&head, secondNodePtr);
  thirdNodePtr = MemoryList_createNode(10);
  MemoryList_insertTail(&head, thirdNodePtr);
  fourthNodePtr = MemoryList_createNode(-20);
  MemoryList_insertHead(&head, fourthNodePtr);
  MemoryList_sort(&head);
  assert(head == fourthNodePtr);
  assert(head->next == firstNodePtr);
  assert(head->next->next == secondNodePtr);
  assert(head->next->next->next == thirdNodePtr);
  assert(head->next->next->next->next == NULL);
  assert(head->item == -20);
  assert(head->next->item == 0);
  assert(head->next->next->item == 5);
  assert(head->next->next->next->item == 10);
  assert(fourthNodePtr->next == firstNodePtr);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Free memory for firstNodePtr, secondNodePtr and thirdNodePtr
  MemoryList_deleteNode(&head, thirdNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);
  MemoryList_deleteNode(&head, secondNodePtr);
  MemoryList_deleteNode(&head, fourthNodePtr);

  // * Sorting a list with five entries (smallest at the front and largest at the end)
  firstNodePtr = MemoryList_createNode(0);
  MemoryList_insertHead(&head, firstNodePtr);
  secondNodePtr = MemoryList_createNode(5);
  MemoryList_insertTail(&head, secondNodePtr);
  thirdNodePtr = MemoryList_createNode(5);
  MemoryList_insertTail(&head, thirdNodePtr);
  fourthNodePtr = MemoryList_createNode(-20);
  MemoryList_insertHead(&head, fourthNodePtr);
  fifthNodePtr = MemoryList_createNode(10);
  MemoryList_insertTail(&head, fifthNodePtr);
  MemoryList_sort(&head);
  assert(head == fourthNodePtr);
  assert(head->next == firstNodePtr);
  assert(head->next->next == secondNodePtr);
  assert(head->next->next->next == thirdNodePtr);
  assert(head->next->next->next->next == fifthNodePtr);
  assert(head->next->next->next->next->next == NULL );
  assert(head->item == -20);
  assert(head->next->item == 0);
  assert(head->next->next->item == 5);
  assert(head->next->next->next->item == 5);
  assert(head->next->next->next->next->item == 10);
  assert(fourthNodePtr->next == firstNodePtr);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == fifthNodePtr);
  assert(fifthNodePtr->next == NULL);

  // * Free memory for firstNodePtr, secondNodePtr and thirdNodePtr
  MemoryList_deleteNode(&head, thirdNodePtr);
  MemoryList_deleteNode(&head, firstNodePtr);
  MemoryList_deleteNode(&head, secondNodePtr);
  MemoryList_deleteNode(&head,fourthNodePtr);
  MemoryList_deleteNode(&head,fifthNodePtr);

  assert(head == NULL);

  printf("Execution finished.\n");

  return 0;
}
