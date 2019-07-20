#include "kallocator.h"

/*
 * Prints message to the terminal on a single line
 * message: message to be printed
 */
void print_allocator_message (charPtr message) {
  printf("%s\n", message);
}

/*
 * Prints an message to the terminal on a single line and exits
 * message: message to be printed
 */
void print_allocator_error_message (charPtr message) {
  printf("%s\n", message);
  exit(-1);
}

/*
 * Handles reassigning compacted blocks
 * before[]: original positions before compact allocation
 * after[]: updated positions after compact allocation
 * blocks[]: blocks some of which are to be reassigned
 * num_compacted_blocks: total number of blocks to reassign
 */
void assign_compacted_blocks (voidPtr* before, voidPtr* after, voidPtr* blocks, int num_compacted_blocks) {
  int j = 0;
  for (int i = 0; i < num_compacted_blocks; i++) {
    for (; blocks[j] != before[i]; j++) {
    }

    blocks[j] = after[i];
  }
}

struct memoryNode {
  voidPtr current;
  voidPtr next;
  int block_size;
};

#define memoryNodePtr memoryNode*

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

struct KAllocator {
  enum allocation_algorithm aalgorithm;
  int size;
  voidPtr memory;
  struct memoryNodePtr free_memory_head;
  struct memoryNodePtr allocated_memory_head;
};

struct KAllocator kallocator;

/*
 * Initializes the contiguous memory allocator
 * _size: indicates the contiguous memory chunk size that is assumed for the rest of the program
 * _aalgorithm: an enum which will determine the algorithm used for allocation in the rest of the program
 */
void initialize_allocator (int _size, enum allocation_algorithm _aalgorithm) {
  assert(_size > 0);

  // * Initialize allocation algorithm
  kallocator.aalgorithm = _aalgorithm;

  // * Initialize contiguous memory chunk size
  kallocator.size = _size;

  // * Initialize dynamic contiguous memory
  kallocator.memory = malloc((size_t)kallocator.size);

  // * Initialize free memory
  struct memoryNodePtr init_free_memory = (struct memoryNodePtr) malloc(sizeof(struct memoryNode));
  init_free_memory->current = kallocator.memory;
  init_free_memory->block_size = kallocator.size;
  init_free_memory->next = NULL;
  MemoryList_insertHead(&kallocator.free_memory_head, init_free_memory);

  // * Initialize allocated memory
  kallocator.allocated_memory_head = NULL;
}

/*
 * Frees all dynamic memory associated with the allocator
 */
void destroy_allocator () {
  // * Frees contiguous memory chunk
  free(kallocator.memory);

  // * Frees all free memory
  MemoryList_deleteAllNodes(&kallocator.free_memory_head);

  // * Frees all allocated memory
  MemoryList_deleteAllNodes(&kallocator.allocated_memory_head);
}

/*
 * Returns a pointer to the allocated block of _size
 * If allocation cannot be satisfied, kalloc returns NULL
 * _size: the size of the block of memory to return
 */
voidPtr kalloc (int _size) {
  if(_size <= 0){
    printf("Error: kalloc memory less or equal to 0\n");
    exit(-1);
  }
  if(_size > MemoryList_findLargestBlockSize(kallocator.free_memory_head)){
    printf("Error: inserting memory larger than largest free chunk\n");
    exit(-1);
  }
  voidPtr ptr = NULL;
  switch (kallocator.aalgorithm) {
    case FIRST_FIT: {
      for (struct memoryNodePtr currentMemoryNodePtr = kallocator.free_memory_head; currentMemoryNodePtr != NULL; currentMemoryNodePtr = currentMemoryNodePtr->next) {
        if (_size <= currentMemoryNodePtr->block_size) {
          // * Assign ptr to memory
          ptr = currentMemoryNodePtr->current;

          if (_size == currentMemoryNodePtr->block_size) {
            // * Remove node from free memory
            MemoryList_deleteNode(&kallocator.free_memory_head, currentMemoryNodePtr);
          } else if (_size < currentMemoryNodePtr->block_size) {
            // * Update node in free memory
            currentMemoryNodePtr->block_size -= _size;
            currentMemoryNodePtr->current += _size;
          }

          // * Add to allocated memory
          struct memoryNodePtr allocated_memory = (struct memoryNodePtr) malloc(sizeof(struct memoryNode));
          allocated_memory->current = ptr;
          allocated_memory->block_size = _size;
          allocated_memory->next = NULL;
          MemoryList_insertTail(&kallocator.allocated_memory_head, allocated_memory);
          MemoryList_sort(&kallocator.allocated_memory_head);

          break;
        }
      }

      break;
    }
    case BEST_FIT: {
      struct memoryNodePtr temp_memory;
      int temp_block = 0;
      for (struct memoryNodePtr currentMemoryNodePtr = kallocator.free_memory_head; currentMemoryNodePtr != NULL; currentMemoryNodePtr = currentMemoryNodePtr->next) {
        if (_size <= currentMemoryNodePtr->block_size) {
          if (temp_block == 0){
            temp_block = currentMemoryNodePtr->block_size;
            temp_memory = currentMemoryNodePtr;
            ptr = currentMemoryNodePtr->current;
          }
          else if (temp_block > currentMemoryNodePtr->block_size) {
            temp_block = currentMemoryNodePtr->block_size;
            temp_memory = currentMemoryNodePtr;
            ptr = temp_memory -> current;
          }
        }
      }

      if (_size == temp_memory->block_size) {
        // * Remove node from free memory
        MemoryList_deleteNode(&kallocator.free_memory_head, temp_memory);
      } else if (_size < temp_memory->block_size) {
        // * Update node in free memory
        temp_memory->block_size -= _size;
        temp_memory->current += _size;
      }

      struct memoryNodePtr allocated_memory = (struct memoryNodePtr) malloc(sizeof(struct memoryNode));
      allocated_memory->current = ptr;
      allocated_memory->block_size = _size;
      allocated_memory->next = NULL;
      MemoryList_insertTail(&kallocator.allocated_memory_head, allocated_memory);
      MemoryList_sort(&kallocator.allocated_memory_head);
      break;
    }
    case WORST_FIT: {
      struct memoryNodePtr temp_memory;
      int tempblock = 0;
      for (struct memoryNodePtr currentMemoryNodePtr = kallocator.free_memory_head; currentMemoryNodePtr != NULL; currentMemoryNodePtr = currentMemoryNodePtr->next) {
        if (_size <= currentMemoryNodePtr->block_size) {
          if(tempblock == 0){
            tempblock = currentMemoryNodePtr->block_size;
            temp_memory = currentMemoryNodePtr;
            ptr = currentMemoryNodePtr->current;
          }
          else if(tempblock < currentMemoryNodePtr->block_size){
            tempblock = currentMemoryNodePtr->block_size;
            temp_memory = currentMemoryNodePtr;
            ptr = temp_memory -> current;
          }
        }
      }

      if (_size == temp_memory->block_size) {
        // * Remove node from free memory
        MemoryList_deleteNode(&kallocator.free_memory_head, temp_memory);
      } else if (_size < temp_memory->block_size) {
        // * Update node in free memory
        temp_memory->block_size -= _size;
        temp_memory->current += _size;
      }

      struct memoryNodePtr allocated_memory = (struct memoryNodePtr) malloc(sizeof(struct memoryNode));
      allocated_memory->current = ptr;
      allocated_memory->block_size = _size;
      allocated_memory->next = NULL;
      MemoryList_insertTail(&kallocator.allocated_memory_head, allocated_memory);
      MemoryList_sort(&kallocator.allocated_memory_head);
      break;
    }
    default: {
      print_allocator_error_message("Unknown allocation algorithm used");
    }
  }

  return ptr;
}

/*
 * Handles merging consecutive free memory blocks
 */
void merge_consecutive_free_memory_blocks (void) {
  for (struct memoryNodePtr freeMemoryPtr = (struct memoryNodePtr) kallocator.free_memory_head; freeMemoryPtr != NULL; ) {
    if (freeMemoryPtr->next && (freeMemoryPtr->current + freeMemoryPtr->block_size == ((struct memoryNodePtr) freeMemoryPtr->next)->current)) {
      freeMemoryPtr->block_size += ((struct memoryNodePtr)freeMemoryPtr->next)->block_size;
      MemoryList_deleteNode(&kallocator.free_memory_head, freeMemoryPtr->next);
      continue;
    } else {
      freeMemoryPtr = freeMemoryPtr->next;
    }
  }
}

/*
 * Takes away the ownership of the block pointed by _ptr
 * _ptr: pointer referencing block of memory to be freed
 */
void kfree (voidPtr _ptr) {
  assert(_ptr != NULL);

  for (struct memoryNodePtr currentMemoryNodePtr = kallocator.allocated_memory_head; currentMemoryNodePtr != NULL; currentMemoryNodePtr = currentMemoryNodePtr->next) {
    if (currentMemoryNodePtr->current == _ptr) {
      struct memoryNodePtr free_memory = (struct memoryNodePtr) malloc(sizeof(struct memoryNode));

      // * Add node to free memory
      free_memory->current = currentMemoryNodePtr->current;
      free_memory->block_size = currentMemoryNodePtr->block_size;
      free_memory->next = NULL;
      MemoryList_insertTail(&kallocator.free_memory_head, free_memory);
      MemoryList_sort(&kallocator.free_memory_head);

      merge_consecutive_free_memory_blocks();

      // * Remove node from allocated memory
      MemoryList_deleteNode(&kallocator.allocated_memory_head, currentMemoryNodePtr);

      break;
    }
  }
}

/*
 * Handles compaction of allocated memory into a contiguous block of allocated memory
 * Returns the number of compacted memory blocks
 * _before: an array of pointers of original locations of allocated memory that have been moved
 * _after: an array of pointers of new locations of allocated memory that have been moved
 */
int compact_allocation (voidPtr* _before, voidPtr* _after) {
  int compacted_size = 0;

  MemoryList_sort(&kallocator.allocated_memory_head);

  int location_index = 0;
  for (struct memoryNodePtr freeMemoryPtr = kallocator.free_memory_head; freeMemoryPtr != NULL; freeMemoryPtr = freeMemoryPtr->next) {
    for (struct memoryNodePtr allocatedMemoryPtr = kallocator.allocated_memory_head; allocatedMemoryPtr != NULL; allocatedMemoryPtr = allocatedMemoryPtr->next) {
      if (allocatedMemoryPtr->current < freeMemoryPtr->current) {
        continue;
      } else {
        _before[location_index] = allocatedMemoryPtr->current;

        memmove(freeMemoryPtr->current, allocatedMemoryPtr->current, allocatedMemoryPtr->block_size);
        freeMemoryPtr->current += allocatedMemoryPtr->block_size;
        allocatedMemoryPtr->current -= freeMemoryPtr->block_size;
        
        merge_consecutive_free_memory_blocks();

        _after[location_index] = allocatedMemoryPtr->current;

        location_index++;
        
        compacted_size++;
      }
    }
  }

  return compacted_size;
}

/*
 * Returns the available memory size
 */
int available_memory () {
  int available_memory_size = 0;

  for (struct memoryNodePtr currentMemoryNodePtr = kallocator.free_memory_head; currentMemoryNodePtr != NULL; currentMemoryNodePtr = currentMemoryNodePtr->next) {
    available_memory_size += currentMemoryNodePtr->block_size;
  }

  return available_memory_size;
}

/*
 * Returns the allocated memory size
 */
int allocated_memory () {
  int allocated_memory_size = 0;

  for (struct memoryNodePtr currentMemoryNodePtr = kallocator.allocated_memory_head; currentMemoryNodePtr != NULL; currentMemoryNodePtr = currentMemoryNodePtr->next) {
    allocated_memory_size += currentMemoryNodePtr->block_size;
  }

  return allocated_memory_size;
}

/*
 * Prints the detailed statistics of the program
 */
void print_statistics () {
  int allocated_size = allocated_memory();
  int allocated_chunks = MemoryList_countNodes(kallocator.allocated_memory_head);
  int free_size = available_memory();
  int free_chunks = MemoryList_countNodes(kallocator.free_memory_head);
  int smallest_free_chunk_size = MemoryList_findSmallestBlockSize(kallocator.free_memory_head);
  int largest_free_chunk_size = MemoryList_findLargestBlockSize(kallocator.free_memory_head);

  printf("Allocated size = %d\n", allocated_size);
  printf("Allocated chunks = %d\n", allocated_chunks);
  printf("Free size = %d\n", free_size);
  printf("Free chunks = %d\n", free_chunks);
  printf("Largest free chunk size = %d\n", largest_free_chunk_size);
  printf("Smallest free chunk size = %d\n", smallest_free_chunk_size);
}