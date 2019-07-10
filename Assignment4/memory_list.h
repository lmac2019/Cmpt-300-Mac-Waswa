#ifndef MEMORY_MemoryList_H
#define MEMORY_MemoryList_H

#include "macros.h"
#include <stdlib.h>

struct memoryNode {
  voidPtr current;
  voidPtr next;
  int block_size;
};

#define memoryNodePtr memoryNode*

struct memoryNodePtr MemoryList_createNode(int block_size, voidPtr block);
void MemoryList_insertHead(struct memoryNodePtr* headRef, struct memoryNodePtr node);
void MemoryList_insertTail(struct memoryNodePtr* headRef, struct memoryNodePtr node);
int MemoryList_countNodes(struct memoryNodePtr head);
struct memoryNodePtr MemoryList_findNode(struct memoryNodePtr head, voidPtr block);
void MemoryList_deleteNode(struct memoryNodePtr* headRef, struct memoryNodePtr node);
void MemoryList_deleteAllNodes(struct memoryNodePtr* headRef);
void MemoryList_sort(struct memoryNodePtr* headRef);

#endif