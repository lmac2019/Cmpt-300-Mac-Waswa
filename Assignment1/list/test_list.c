#include "list.h"
#include <stdio.h>
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
   * Tests for List_insertHead
   */
  struct nodeStructPtr head;
  struct nodeStructPtr firstNode;
  struct nodeStructPtr secondNode;
  struct nodeStructPtr thirdNode;
  struct nodeStructPtr fourthNode;
  struct nodeStructPtr fifthNode;

  head = NULL;
  firstNode = List_createNode(1);
  List_insertHead(&head, firstNode);
  assert(head->item == 1);

  head = List_createNode(0);
  firstNode = List_createNode(1);
  List_insertHead(&head, firstNode);
  assert(head->item == 1);

  head = List_createNode(0);
  secondNode = List_createNode(2);
  head->next = secondNode;
  firstNode = List_createNode(1);
  List_insertHead(&head, firstNode);
  assert(head->item == 1);

  head = List_createNode(0);
  secondNode = List_createNode(2);
  head->next = secondNode;
  thirdNode = List_createNode(2);
  secondNode->next = thirdNode;
  firstNode = List_createNode(-1);
  List_insertHead(&head, firstNode);
  assert(head->item == -1);

  /*
   * Tests for List_insertTail
   */
  head = NULL;
  firstNode = List_createNode(0);
  List_insertTail(&head, firstNode);
  assert(head->item == 0);

  firstNode = List_createNode(1);
  head = firstNode;
  secondNode = List_createNode(2);
  firstNode->next = secondNode;
  thirdNode = List_createNode(3);
  List_insertTail(&head, thirdNode);
  assert(head->next->next->item == 3);

  firstNode = List_createNode(1);
  head = firstNode;
  secondNode = List_createNode(2);
  firstNode->next = secondNode;
  thirdNode = List_createNode(3);
  secondNode->next = thirdNode;
  fourthNode = List_createNode(4);
  List_insertTail(&head, fourthNode);
  assert(head->next->next->next->item == 4);

  /*
   * Tests for List_countNodes
   */
  head = NULL;
  assert(List_countNodes(head) == 0);

  firstNode = List_createNode(0);
  head = firstNode;
  assert(List_countNodes(head) == 1);

  firstNode = List_createNode(1);
  head = firstNode;
  secondNode = List_createNode(2);
  firstNode->next = secondNode;
  assert(List_countNodes(head) == 2);

  firstNode = List_createNode(1);
  head = firstNode;
  secondNode = List_createNode(2);
  firstNode->next = secondNode;
  thirdNode = List_createNode(3);
  secondNode->next = thirdNode;
  assert(List_countNodes(head) == 3);

  firstNode = List_createNode(1);
  head = firstNode;
  secondNode = List_createNode(2);
  firstNode->next = secondNode;
  thirdNode = List_createNode(3);
  secondNode->next = thirdNode;
  fourthNode = List_createNode(4);
  thirdNode->next = fourthNode;
  assert(List_countNodes(head) == 4);

  /*
   * Tests for List_findNode
   */
  firstNode = List_createNode(1);
  head = firstNode;
  secondNode = List_createNode(2);
  firstNode->next = secondNode;
  thirdNode = List_createNode(3);
  secondNode->next = thirdNode;
  fourthNode = List_createNode(4);
  thirdNode->next = fourthNode;
  fifthNode = List_createNode(5);

  assert(List_findNode(head, firstNode->item) == firstNode);
  assert(List_findNode(head, secondNode->item) == secondNode);
  assert(List_findNode(head, thirdNode->item) == thirdNode);
  assert(List_findNode(head, fourthNode->item) == fourthNode);
  assert(List_findNode(head, fifthNode->item) == NULL);

  head = NULL;
  assert(List_findNode(head, fifthNode->item) == NULL);

  /*
   * Tests for List_deleteNode
   */

  // * Remove first node in a linked list with one node
  firstNode = List_createNode(0);
  head = firstNode;
  List_deleteNode(&head, firstNode);
  assert(List_findNode(head, firstNode->item) == NULL);
  assert(head == NULL);

  // * Remove first node in a linked list with two nodes
  firstNode = List_createNode(0);
  head = firstNode;
  secondNode = List_createNode(1);
  List_insertTail(&head, secondNode);
  List_deleteNode(&head, firstNode);
  assert(List_findNode(head, firstNode->item) == NULL);
  assert(List_findNode(head, secondNode->item) == secondNode);
  assert(head == secondNode);
  assert(secondNode->next == NULL);

  // * Remove second node in a linked list with two nodes
  firstNode = List_createNode(0);
  head = firstNode;
  secondNode = List_createNode(1);
  List_insertTail(&head, secondNode);
  List_deleteNode(&head, secondNode);
  assert(List_findNode(head, firstNode->item) == firstNode);
  assert(List_findNode(head, secondNode->item) == NULL);
  assert(head == firstNode);
  assert(firstNode->next == NULL);

  // * Remove first node in a linked list with three nodes
  firstNode = List_createNode(0);
  head = firstNode;
  secondNode = List_createNode(1);
  List_insertTail(&head, secondNode);
  thirdNode = List_createNode(2);
  List_insertTail(&head, thirdNode);
  List_deleteNode(&head, firstNode);
  assert(List_findNode(head, firstNode->item) == NULL);
  assert(List_findNode(head, secondNode->item) == secondNode);
  assert(List_findNode(head, thirdNode->item) == thirdNode);
  assert(head == secondNode);
  assert(head->next == thirdNode);
  assert(thirdNode->next == NULL);

  // * Remove second node in a linked list with three nodes
  firstNode = List_createNode(0);
  head = firstNode;
  secondNode = List_createNode(1);
  List_insertTail(&head, secondNode);
  thirdNode = List_createNode(2);
  List_insertTail(&head, thirdNode);
  List_deleteNode(&head, secondNode);
  assert(List_findNode(head, firstNode->item) == firstNode);
  assert(List_findNode(head, secondNode->item) == NULL);
  assert(List_findNode(head, thirdNode->item) == thirdNode);
  assert(head == firstNode);
  assert(firstNode->next == thirdNode);
  assert(thirdNode->next == NULL);

  // * Remove third node in a linked list with three nodes
  firstNode = List_createNode(0);
  head = firstNode;
  secondNode = List_createNode(1);
  List_insertTail(&head, secondNode);
  thirdNode = List_createNode(2);
  List_insertTail(&head, thirdNode);
  List_deleteNode(&head, thirdNode);
  assert(List_findNode(head, firstNode->item) == firstNode);
  assert(List_findNode(head, secondNode->item) == secondNode);
  assert(List_findNode(head, thirdNode->item) == NULL);
  assert(head == firstNode);
  assert(firstNode->next == secondNode);
  assert(secondNode->next == NULL);

  /*
  * Tests for List_sort
  */
  head = NULL;
  List_sort(&head);
  assert(head == NULL);

  firstNode = List_createNode(1);
  head = firstNode;
  List_sort(&head);
  assert(head->item == 1);
  assert(head->next == NULL);

  firstNode = List_createNode(1);
  head = firstNode;
  secondNode = List_createNode(0);
  List_insertTail(&head, secondNode);
  List_sort(&head);
  assert(head->item == 0);
  assert(head->next->item == 1);

  firstNode = List_createNode(-20);
  head = firstNode;
  secondNode = List_createNode(0);
  List_insertTail(&head, secondNode);
  thirdNode = List_createNode(5);
  List_insertTail(&head, thirdNode);
  List_sort(&head);
  assert(head->item == -20);
  assert(head->next->item == 0);
  assert(head->next->next->item == 5);

  firstNode = List_createNode(2);
  head = firstNode;
  secondNode = List_createNode(0);
  List_insertTail(&head, secondNode);
  thirdNode = List_createNode(6);
  List_insertTail(&head, thirdNode);
  fourthNode = List_createNode(5);
  List_insertTail(&head, fourthNode);
  List_sort(&head);
  assert(head->item == 0);
  assert(head->next->item == 2);
  assert(head->next->next->item == 5);
  assert(head->next->next->next->item == 6);

  firstNode = List_createNode(3);
  head = firstNode;
  secondNode = List_createNode(1);
  List_insertTail(&head, secondNode);
  thirdNode = List_createNode(2);
  List_insertTail(&head, thirdNode);
  fourthNode = List_createNode(15);
  List_insertTail(&head, fourthNode);
  fifthNode = List_createNode(0);
  List_insertTail(&head, fifthNode);
  List_sort(&head);
  assert(head->item == 0);
  assert(head->next->item == 1);
  assert(head->next->next->item == 2);
  assert(head->next->next->next->item == 3);
  assert(head->next->next->next->next->item == 15);

  printf("Execution finished.\n");

  return 0;
}