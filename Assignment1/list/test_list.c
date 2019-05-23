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
  struct nodeStructPtr firstNode = List_createNode(22);
  struct nodeStructPtr secondNode = List_createNode(132);
  struct nodeStructPtr thirdNode = List_createNode(43);
  struct nodeStructPtr fourthNode = List_createNode(-123);
  struct nodeStructPtr fifthNode = List_createNode(-234);

  // * No nodes added to linked list
  assert(head == NULL);

  // * firstNode added to head of linked list
  List_insertHead(&head, firstNode);
  assert(head == firstNode);
  assert(firstNode->next == NULL);

  // * secondNode added to head of linked list
  List_insertHead(&head, secondNode);
  assert(head == secondNode);
  assert(secondNode->next == firstNode);
  assert(firstNode->next == NULL);

  // * thirdNode, fourthNode and fifthNode added to head of linked list sequentially
  List_insertHead(&head, thirdNode);
  List_insertHead(&head, fourthNode);
  List_insertHead(&head, fifthNode);
  assert(head == fifthNode);
  assert(fifthNode->next == fourthNode);
  assert(fourthNode->next == thirdNode);
  assert(thirdNode->next == secondNode);
  assert(secondNode->next == firstNode);
  assert(firstNode->next == NULL);

  // * Free memory for firstNode, secondNode, thirdNode, fourthNode and fifthNode
  free(firstNode);
  free(secondNode);
  free(thirdNode);
  free(fourthNode);
  free(fifthNode);

  /*
   * Tests for List_insertTail
   */
  head = NULL;
  firstNode = List_createNode(22);
  secondNode = List_createNode(132);
  thirdNode = List_createNode(43);
  fourthNode = List_createNode(-123);
  fifthNode = List_createNode(-234);

  // * No nodes added to linked list
  assert(head == NULL);

  // * firstNode added to tail of linked list
  List_insertTail(&head, firstNode);
  assert(head == firstNode);
  assert(firstNode->next == NULL);

  // * secondNode added to tail of linked list
  List_insertTail(&head, secondNode);
  assert(head == firstNode);
  assert(firstNode->next == secondNode);
  assert(secondNode->next == NULL);

  // * thirdNode, fourthNode, fifthNode added to tail of linked list sequentially
  List_insertTail(&head, thirdNode);
  List_insertTail(&head, fourthNode);
  List_insertTail(&head, fifthNode);
  assert(head == firstNode);
  assert(firstNode->next == secondNode);
  assert(secondNode->next == thirdNode);
  assert(thirdNode->next == fourthNode);
  assert(fourthNode->next == fifthNode);
  assert(fifthNode->next == NULL);

  // * Free memory for firstNode, secondNode, thirdNode, fourthNode and fifthNode
  free(fifthNode);
  free(fourthNode);
  free(thirdNode);
  free(secondNode);
  free(firstNode);

  /*
   * Tests for List_countNodes
   */
  head = NULL;
  firstNode = List_createNode(22);
  // secondNode = List_createNode(132);
  // thirdNode = List_createNode(43);
  // fourthNode = List_createNode(-123);
  // fifthNode = List_createNode(-234);

  // * No nodes added to linked list
  assert(List_countNodes(head) == 0);

  // * One node added to linked list (added to tail)
  List_insertTail(&head, firstNode);
  assert(List_countNodes(head) == 1);

  // * Free memory for firstNode
  free(firstNode);

  // firstNode = List_createNode(22);

  // // * One node added to linked list (added to head)
  // List_insertHead(&head, firstNode);
  // assert(List_countNodes(head) == 1);

  // // * Two nodes added to linked list (added to head)
  // List_insertHead(&head, secondNode);
  // assert(List_countNodes(head) == 2);

  // // * Free memory for firstNode and secondNode
  // free(firstNode);
  // free(secondNode);

  // firstNode = List_createNode(22);
  // secondNode = List_createNode(132);

  // // * Two nodes added to linked list (added to tail)
  // List_insertTail(&head, firstNode);
  // List_insertTail(&head, secondNode);
  // assert(List_countNodes(head) == 2);

  // // * Free memory for secondNode and firstNode
  // free(secondNode);
  // free(firstNode);

  // firstNode = List_createNode(22);
  // secondNode = List_createNode(132);

  // // * Two nodes added to linked list (first one added to tail, second one added to head)
  // List_insertTail(&head, firstNode);
  // List_insertHead(&head, secondNode);
  // assert(List_countNodes(head) == 2);

  // // * Free memory for firstNode and secondNode
  // free(firstNode);
  // free(secondNode);

  // firstNode = List_createNode(22);
  // secondNode = List_createNode(132);

  // // * Two nodes added to linked list (first one added to head, second one added to tail)
  // List_insertHead(&head, firstNode);
  // List_insertTail(&head, secondNode);
  // assert(List_countNodes(head) == 2);

  // // * Free memory for secondNode and firstNode
  // free(secondNode);
  // free(firstNode);

  // // * Three nodes added to linked list (added to tail)
  // List_insertTail(&head, thirdNode);
  // List_insertTail(&head, fourthNode);
  // List_insertTail(&head, fifthNode);
  // assert(List_countNodes(head) == 3);

  // // * Free memory for fifthNode, fourthNode and thirdNode
  // free(fifthNode);
  // free(fourthNode);
  // free(thirdNode);

  // /*
  //  * Tests for List_findNode
  //  */
  // head = NULL;
  // firstNode = List_createNode(22);
  // secondNode = List_createNode(132);
  // thirdNode = List_createNode(43);
  // fourthNode = List_createNode(-123);

  // // * Four nodes added sequentially to the tail
  // List_insertTail(&head, firstNode);
  // List_insertTail(&head, secondNode);
  // List_insertTail(&head, thirdNode);
  // List_insertTail(&head, fourthNode);
  // assert(List_findNode(head, firstNode->item) == firstNode);
  // assert(List_findNode(head, secondNode->item) == secondNode);
  // assert(List_findNode(head, thirdNode->item) == thirdNode);
  // assert(List_findNode(head, fourthNode->item) == fourthNode);
  // assert(List_findNode(head, fifthNode->item) == NULL);

  // // * Free memory for fourthNode, thirdNode, secondNode and firstNode
  // free(fourthNode);
  // free(thirdNode);
  // free(secondNode);
  // free(firstNode);

  // head = NULL;
  // assert(List_findNode(head, firstNode->item) == NULL);
  // assert(List_findNode(head, secondNode->item) == NULL);
  // assert(List_findNode(head, thirdNode->item) == NULL);
  // assert(List_findNode(head, fourthNode->item) == NULL);
  // assert(List_findNode(head, fifthNode->item) == NULL);

  // /*
  //  * Tests for List_deleteNode
  //  */
  // firstNode = List_createNode(22);
  // secondNode = List_createNode(132);
  // thirdNode = List_createNode(43);

  // // * Remove first node in a linked list with one node (added to the tail)
  // List_insertTail(&head, firstNode);
  // List_deleteNode(&head, firstNode);
  // assert(List_findNode(head, firstNode->item) == NULL);
  // assert(head == NULL);

  // // * Remove first node in a linked list with one node (added to the head)
  // firstNode = List_createNode(100);
  // List_insertHead(&head, firstNode);
  // List_deleteNode(&head, firstNode);
  // assert(List_findNode(head, firstNode->item) == NULL);
  // assert(head == NULL);

  // // * Remove first node in a linked list with two nodes
  // firstNode = List_createNode(102);
  // List_insertTail(&head, firstNode);
  // List_insertTail(&head, secondNode);
  // List_deleteNode(&head, firstNode);
  // assert(List_findNode(head, firstNode->item) == NULL);
  // assert(List_findNode(head, secondNode->item) == secondNode);
  // assert(head == secondNode);
  // assert(secondNode->next == NULL);

  // // * Remove last node in a linked list with two nodes
  // firstNode = List_createNode(111);
  // List_insertHead(&head, firstNode);
  // List_deleteNode(&head, secondNode);
  // assert(List_findNode(head, firstNode->item) == firstNode);
  // assert(List_findNode(head, secondNode->item) == NULL);
  // assert(head == firstNode);
  // assert(firstNode->next == NULL);

  // // * Remove first node in a linked list with three nodes
  // secondNode = List_createNode(32);
  // List_insertTail(&head, secondNode);
  // List_insertTail(&head, thirdNode);
  // List_deleteNode(&head, firstNode);
  // assert(List_findNode(head, firstNode->item) == NULL);
  // assert(List_findNode(head, secondNode->item) == secondNode);
  // assert(List_findNode(head, thirdNode->item) == thirdNode);
  // assert(head == secondNode);
  // assert(head->next == thirdNode);
  // assert(thirdNode->next == NULL);

  // // * Remove middle node in a linked list with three nodes
  // firstNode = List_createNode(19);
  // List_insertHead(&head, firstNode);
  // List_deleteNode(&head, secondNode);
  // assert(List_findNode(head, firstNode->item) == firstNode);
  // assert(List_findNode(head, secondNode->item) == NULL);
  // assert(List_findNode(head, thirdNode->item) == thirdNode);
  // assert(head == firstNode);
  // assert(firstNode->next == thirdNode);
  // assert(thirdNode->next == NULL);

  // // * Remove last node in a linked list with three nodes

  // // * Free memory for thirdNode
  // free(thirdNode);

  // secondNode = List_createNode(19);
  // List_insertTail(&head, secondNode);
  // thirdNode = List_createNode(24);
  // List_insertTail(&head, thirdNode);
  // List_deleteNode(&head, thirdNode);
  // assert(List_findNode(head, firstNode->item) == firstNode);
  // assert(List_findNode(head, secondNode->item) == secondNode);
  // assert(List_findNode(head, thirdNode->item) == NULL);
  // assert(head == firstNode);
  // assert(firstNode->next == secondNode);
  // assert(secondNode->next == NULL);

  // // * Free memory for secondNode and thirdNode
  // free(secondNode);
  // free(firstNode);

  // /*
  // * Tests for List_sort
  // */
  // head = NULL;
  // firstNode = List_createNode(22);
  // secondNode = List_createNode(132);
  // thirdNode = List_createNode(43);

  // // * Sorting an empty list
  // List_sort(&head);
  // assert(head == NULL);

  // // * Sorting a list with one entry (added to the head)
  // List_insertHead(&head, firstNode);
  // List_sort(&head);
  // assert(head == firstNode);
  // assert(head->next == NULL);

  // // * Free memory for firstNode
  // List_deleteNode(&head, firstNode);

  // // * Sorting a list with one entry (added to the tail)
  // firstNode = List_createNode(2);
  // List_insertTail(&head, firstNode);
  // List_sort(&head);
  // assert(head == firstNode);
  // assert(head->next == NULL);

  // // * Sorting a list with two entries (originally unsorted)
  // List_insertHead(&head, secondNode);
  // List_sort(&head);
  // assert(head == secondNode);
  // assert(head->next == firstNode);

  // // * Free memory for firstNode
  // List_deleteNode(&head, firstNode);

  // // * Sorting a list with two entries (originally sorted with different item values)
  // firstNode = List_createNode(2);
  // List_insertHead(&head, firstNode);
  // List_sort(&head);
  // assert(head == firstNode);
  // assert(head->next == secondNode);

  // // * Free memory for secondNode and firstNode
  // List_deleteNode(&head, secondNode);
  // List_deleteNode(&head, firstNode);

  // // * Sorting a list with two entries (originally sorted with the same item values)
  // firstNode = List_createNode(2);
  // List_insertTail(&head, firstNode);
  // secondNode = List_createNode(2);
  // List_insertTail(&head, secondNode);
  // List_sort(&head);
  // assert(head == firstNode);
  // assert(head->next == secondNode);

  // // * Free memory for secondNode and firstNode
  // List_deleteNode(&head, secondNode);
  // List_deleteNode(&head, firstNode);

  // // * Sorting a list with three entries (smallest at the front and largest at the end)
  // firstNode = List_createNode(-20);
  // List_insertTail(&head, firstNode);
  // secondNode = List_createNode(0);
  // List_insertTail(&head, secondNode);
  // List_insertTail(&head, thirdNode);
  // List_sort(&head);
  // assert(head == firstNode);
  // assert(head->next == secondNode);
  // assert(head->next->next == thirdNode);

  // // * Free memory for secondNode and firstNode
  // List_deleteNode(&head, secondNode);
  // List_deleteNode(&head, firstNode);

  // // * Sorting a list with three entries (largest at the front and smallest at the end)
  // firstNode = List_createNode(-20);
  // List_insertTail(&head, firstNode);
  // secondNode = List_createNode(0);
  // List_insertHead(&head, secondNode);
  // List_sort(&head);
  // assert(head == firstNode);
  // assert(head->next == secondNode);
  // assert(head->next->next == thirdNode);

  // // * Free memory for firstNode, secondNode and thirdNode
  // List_deleteNode(&head, firstNode);
  // List_deleteNode(&head, secondNode);
  // List_deleteNode(&head, thirdNode);

  printf("Execution finished.\n");

  return 0;
}