#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>

int main (int argc, char **argv) {
  printf("Starting tests for list...\n");

  /*
   * Tests for List_createNode
   */
  struct nodeStructPtr createdNode;

  createdNode = List_createNode(-100);
  assert(createdNode->item == -100);

  createdNode = List_createNode(0);
  assert(createdNode->item == 0);

  createdNode = List_createNode(100);
  assert(createdNode->item == 100);

  /*
   * Free memory for createdNode
   */
  free(createdNode);
  
  /*
   * Tests for List_insertHead
   */
  struct nodeStructPtr head = NULL;
  struct nodeStructPtr firstNodePtr = List_createNode(22);
  struct nodeStructPtr secondNodePtr = List_createNode(132);
  struct nodeStructPtr thirdNodePtr = List_createNode(43);
  struct nodeStructPtr fourthNodePtr = List_createNode(-123);
  struct nodeStructPtr fifthNodePtr = List_createNode(-234);

  // * No nodes added to linked list
  assert(head == NULL);

  // * firstNodePtr added to head of linked list
  List_insertHead(&head, firstNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * secondNodePtr added to head of linked list
  List_insertHead(&head, secondNodePtr);
  assert(head == secondNodePtr);
  assert(secondNodePtr->next == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * thirdNodePtr, fourthNodePtr and fifthNodePtr added to head of linked list sequentially
  List_insertHead(&head, thirdNodePtr);
  List_insertHead(&head, fourthNodePtr);
  List_insertHead(&head, fifthNodePtr);
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
   * Tests for List_insertTail
   */
  head = NULL;
  firstNodePtr = List_createNode(22);
  secondNodePtr = List_createNode(132);
  thirdNodePtr = List_createNode(43);
  fourthNodePtr = List_createNode(-123);
  fifthNodePtr = List_createNode(-234);

  // * No nodes added to linked list
  assert(head == NULL);

  // * firstNodePtr added to tail of linked list
  List_insertTail(&head, firstNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * secondNodePtr added to tail of linked list
  List_insertTail(&head, secondNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == secondNodePtr);
  assert(secondNodePtr->next == NULL);

  // * thirdNodePtr, fourthNodePtr, fifthNodePtr added to tail of linked list sequentially
  List_insertTail(&head, thirdNodePtr);
  List_insertTail(&head, fourthNodePtr);
  List_insertTail(&head, fifthNodePtr);
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
   * Tests for List_countNodes
   */
  head = NULL;
  firstNodePtr = List_createNode(22);
  secondNodePtr = List_createNode(132);
  thirdNodePtr = List_createNode(43);
  fourthNodePtr = List_createNode(-123);
  fifthNodePtr = List_createNode(-234);

  // * No nodes added to linked list
  assert(List_countNodes(head) == 0);

  // * One node added to linked list (added to tail)
  List_insertTail(&head, firstNodePtr);
  assert(List_countNodes(head) == 1);

  // * Free memory for firstNodePtr
  free(firstNodePtr);

  head = NULL;
  firstNodePtr = List_createNode(22);

  // * One node added to linked list (added to head)
  List_insertHead(&head, firstNodePtr);
  assert(List_countNodes(head) == 1);

  // * Two nodes added to linked list (added to head)
  List_insertHead(&head, secondNodePtr);
  assert(List_countNodes(head) == 2);

  // * Free memory for firstNodePtr and secondNodePtr
  free(firstNodePtr);
  free(secondNodePtr);

  head = NULL;
  firstNodePtr = List_createNode(22);
  secondNodePtr = List_createNode(132);

  // * Two nodes added to linked list (added to tail)
  List_insertTail(&head, firstNodePtr);
  List_insertTail(&head, secondNodePtr);
  assert(List_countNodes(head) == 2);

  // * Free memory for secondNodePtr and firstNodePtr
  free(secondNodePtr);
  free(firstNodePtr);
  
  head = NULL;
  firstNodePtr = List_createNode(22);
  secondNodePtr = List_createNode(132);

  // * Two nodes added to linked list (first one added to tail, second one added to head)
  List_insertTail(&head, firstNodePtr);
  List_insertHead(&head, secondNodePtr);
  assert(List_countNodes(head) == 2);

  // * Free memory for firstNodePtr and secondNodePtr
  free(firstNodePtr);
  free(secondNodePtr);
  
  head = NULL;
  firstNodePtr = List_createNode(22);
  secondNodePtr = List_createNode(132);

  // * Two nodes added to linked list (first one added to head, second one added to tail)
  List_insertHead(&head, firstNodePtr);
  List_insertTail(&head, secondNodePtr);
  assert(List_countNodes(head) == 2);

  // * Free memory for secondNodePtr and firstNodePtr
  free(secondNodePtr);
  free(firstNodePtr);

  head = NULL;

  // * Three nodes added to linked list (added to tail)
  List_insertTail(&head, thirdNodePtr);
  List_insertTail(&head, fourthNodePtr);
  List_insertTail(&head, fifthNodePtr);
  assert(List_countNodes(head) == 3);

  // * Free memory for fifthNodePtr, fourthNodePtr and thirdNodePtr
  free(fifthNodePtr);
  free(fourthNodePtr);
  free(thirdNodePtr);

  /*
   * Tests for List_findNode
   */
  head = NULL;
  firstNodePtr = List_createNode(22);
  secondNodePtr = List_createNode(132);
  thirdNodePtr = List_createNode(43);
  fourthNodePtr = List_createNode(-123);
  fifthNodePtr = List_createNode(-456);

  // * Four nodes added sequentially to the tail
  List_insertTail(&head, firstNodePtr);
  List_insertTail(&head, secondNodePtr);
  List_insertTail(&head, thirdNodePtr);
  List_insertTail(&head, fourthNodePtr);
  assert(List_findNode(head, firstNodePtr->item) == firstNodePtr);
  assert(List_findNode(head, secondNodePtr->item) == secondNodePtr);
  assert(List_findNode(head, thirdNodePtr->item) == thirdNodePtr);
  assert(List_findNode(head, fourthNodePtr->item) == fourthNodePtr);
  assert(List_findNode(head, fifthNodePtr->item) == NULL);

  // * Free memory for fifthNodePtr, fourthNodePtr, thirdNodePtr, secondNodePtr and firstNodePtr
  free(fifthNodePtr);
  free(fourthNodePtr);
  free(thirdNodePtr);
  free(secondNodePtr);
  free(firstNodePtr);

  head = NULL;
  assert(List_findNode(head, firstNodePtr->item) == NULL);
  assert(List_findNode(head, secondNodePtr->item) == NULL);
  assert(List_findNode(head, thirdNodePtr->item) == NULL);
  assert(List_findNode(head, fourthNodePtr->item) == NULL);
  assert(List_findNode(head, fifthNodePtr->item) == NULL);

  /*
   * Tests for List_deleteNode
   */
  firstNodePtr = List_createNode(22);
  secondNodePtr = List_createNode(132);
  thirdNodePtr = List_createNode(43);

  // * Remove first node in a linked list with one node (added to the tail)
  List_insertTail(&head, firstNodePtr);
  List_deleteNode(&head, firstNodePtr);
  assert(List_findNode(head, firstNodePtr->item) == NULL);
  assert(head == NULL);

  // * Remove first node in a linked list with one node (added to the head)
  firstNodePtr = List_createNode(100);
  List_insertHead(&head, firstNodePtr);
  List_deleteNode(&head, firstNodePtr);
  assert(List_findNode(head, firstNodePtr->item) == NULL);
  assert(head == NULL);

  // * Remove first node in a linked list with two nodes
  firstNodePtr = List_createNode(102);
  List_insertTail(&head, firstNodePtr);
  List_insertTail(&head, secondNodePtr);
  List_deleteNode(&head, firstNodePtr);
  assert(List_findNode(head, firstNodePtr->item) == NULL);
  assert(List_findNode(head, secondNodePtr->item) == secondNodePtr);
  assert(head == secondNodePtr);
  assert(secondNodePtr->next == NULL);

  // * Remove last node in a linked list with two nodes
  firstNodePtr = List_createNode(111);
  List_insertHead(&head, firstNodePtr);
  List_deleteNode(&head, secondNodePtr);
  assert(List_findNode(head, firstNodePtr->item) == firstNodePtr);
  assert(List_findNode(head, secondNodePtr->item) == NULL);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == NULL);

  // * Remove first node in a linked list with three nodes
  secondNodePtr = List_createNode(32);
  List_insertTail(&head, secondNodePtr);
  List_insertTail(&head, thirdNodePtr);
  List_deleteNode(&head, firstNodePtr);
  assert(List_findNode(head, firstNodePtr->item) == NULL);
  assert(List_findNode(head, secondNodePtr->item) == secondNodePtr);
  assert(List_findNode(head, thirdNodePtr->item) == thirdNodePtr);
  assert(head == secondNodePtr);
  assert(head->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Remove middle node in a linked list with three nodes
  firstNodePtr = List_createNode(19);
  List_insertHead(&head, firstNodePtr);
  List_deleteNode(&head, secondNodePtr);
  assert(List_findNode(head, firstNodePtr->item) == firstNodePtr);
  assert(List_findNode(head, secondNodePtr->item) == NULL);
  assert(List_findNode(head, thirdNodePtr->item) == thirdNodePtr);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Remove last node in a linked list with three nodes
  secondNodePtr = List_createNode(119);
  List_insertTail(&head, secondNodePtr);
  List_deleteNode(&head, secondNodePtr);
  assert(List_findNode(head, firstNodePtr->item) == firstNodePtr);
  assert(List_findNode(head, thirdNodePtr->item) == thirdNodePtr);
  assert(List_findNode(head, secondNodePtr->item) == NULL);
  assert(head == firstNodePtr);
  assert(firstNodePtr->next == thirdNodePtr);
  assert(thirdNodePtr->next == NULL);

  // * Free memory for secondNodePtr and thirdNodePtr
  free(thirdNodePtr);
  free(firstNodePtr);

  /*
  * Tests for List_sort
  */
  head = NULL;
  firstNodePtr = List_createNode(22);
  secondNodePtr = List_createNode(132);
  thirdNodePtr = List_createNode(43);

  // * Sorting an empty list
  List_sort(&head);
  assert(head == NULL);

  // * Sorting a list with one entry (added to the head)
  List_insertHead(&head, firstNodePtr);
  List_sort(&head);
  assert(head->item == 22);
  assert(head->next == NULL);

  // * Free memory for firstNodePtr
  List_deleteNode(&head, firstNodePtr);

  // * Sorting a list with one entry (added to the tail)
  firstNodePtr = List_createNode(2);
  List_insertTail(&head, firstNodePtr);
  List_sort(&head);
  assert(head->item == 2);
  assert(head->next == NULL);

  // * Sorting a list with two entries (originally unsorted)
  List_insertHead(&head, secondNodePtr);
  List_sort(&head);
  assert(head->item == 2);
  assert(head->next->item == 132);

  // * Free memory for secondNodePtr
  List_deleteNode(&head, firstNodePtr);
  
  // * Sorting a list with two entries (originally sorted with different item values)
  firstNodePtr = List_createNode(1);
  List_insertTail(&head, firstNodePtr);
  List_sort(&head);
  assert(head->item == 1);
  assert(head->next->item == 2);

  // * Free memory for secondNodePtr and firstNodePtr
  List_deleteNode(&head, secondNodePtr);
  List_deleteNode(&head, firstNodePtr);

  // * Sorting a list with two entries (originally sorted with the same item values)
  firstNodePtr = List_createNode(7);
  List_insertTail(&head, firstNodePtr);
  secondNodePtr = List_createNode(7);
  List_insertTail(&head, secondNodePtr);
  List_sort(&head);
  assert(head->item == 7);
  assert(head->next->item == 7);

  // * Free memory for secondNodePtr and firstNodePtr
  List_deleteNode(&head, secondNodePtr);
  List_deleteNode(&head, firstNodePtr);

  // * Sorting a list with three entries (smallest at the front and largest at the end)
  firstNodePtr = List_createNode(-20);
  List_insertTail(&head, firstNodePtr);
  secondNodePtr = List_createNode(10);
  List_insertTail(&head, secondNodePtr);
  List_insertTail(&head, thirdNodePtr);
  List_sort(&head);
  assert(head->item == -20);
  assert(head->next->item == 10);
  assert(head->next->next->item == 43);

  // * Free memory for secondNodePtr and firstNodePtr
  List_deleteNode(&head, secondNodePtr);
  List_deleteNode(&head, firstNodePtr);

  // * Sorting a list with three entries (largest at the front and smallest at the end)
  firstNodePtr = List_createNode(1);
  List_insertTail(&head, firstNodePtr);
  secondNodePtr = List_createNode(-20);
  List_insertTail(&head, secondNodePtr);
  List_sort(&head);
  assert(head->item == -20);
  assert(head->next->item == 1);
  assert(head->next->next->item == 43);
  // head -> thirdNodePtr(-20) -> firstNodePtr(1) -> secondNodePtr(43)

  // * Free memory for firstNodePtr, secondNodePtr and thirdNodePtr
  List_deleteNode(&head, firstNodePtr);
  List_deleteNode(&head, secondNodePtr);
  List_deleteNode(&head, thirdNodePtr);

  // * Ensure all memory is freed
  assert(head == NULL);

  printf("Execution finished.\n");

  return 0;
}