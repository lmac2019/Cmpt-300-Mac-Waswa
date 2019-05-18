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

  createdNode = List_createNode(0);
  assert(createdNode->item == 0);

  createdNode = List_createNode(-100);
  assert(createdNode->item == -100);

  createdNode = List_createNode(100);
  assert(createdNode->item == 100);

  /*
   * Tests for List_insertHead
   */
  struct nodeStructPtr head;
  struct nodeStructPtr firstNode;

  head = NULL;
  firstNode = List_createNode(0);
  List_insertHead(&head, firstNode);
  assert(head->item == 0);

  head = List_createNode(1);
  firstNode = List_createNode(0);
  List_insertHead(&head, firstNode);
  assert(head->item == 0);

  /*
   * Tests for List_insertTail
   */

  /*
   * Tests for List_countNodes
   */

  /*
   * Tests for List_findNode
   */

  /*
   * Tests for List_deleteNode
   */

  /*
   * Tests for List_sort
   */

  printf("Execution finished.\n");

  return 0;
}