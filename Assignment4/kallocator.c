#include "kallocator.h"
#include "memory_list.h"

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