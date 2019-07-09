#ifndef MEMORY_LIST_H
#define MEMORY_LIST_H

#include "macros.h"
#include <stdlib.h>

struct memoryNode {
  voidPtr current;
  voidPtr next;
  int block_size;
};

#define memoryNodePtr memoryNode*

struct memoryNodePtr List_createNode(int block_size, voidPtr block);
void List_insertHead(struct memoryNodePtr* headRef, struct memoryNodePtr node);
void List_insertTail(struct memoryNodePtr* headRef, struct memoryNodePtr node);
int List_countNodes(struct memoryNodePtr head);
struct memoryNodePtr List_findNode(struct memoryNodePtr head, voidPtr block);
void List_deleteNode(struct memoryNodePtr* headRef, struct memoryNodePtr node);
void List_sort(struct memoryNodePtr* headRef);

#endif