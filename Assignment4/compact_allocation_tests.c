#include "compact_allocation_tests.h"
#include "allocator_helpers.h"

/*
 * Performs a compaction test for characters that are scattered in the 
 * contiguous memory allocator
 */
void compact_allocation_scattered_characters (void) {
  int size = 24;
  print_allocator_message("\ncompact_allocation_scattered_characters\n");

  initialize_allocator(size, FIRST_FIT);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  for (int i = 0; i < 24; ++i) {
    if (i <= 6 && i % 2 == 0) {
      continue;
    }

    if (i > 6 && i <= 8) {
      printf("Freeing characters[%d]\n", i);
      kfree(characters[i]);
      characters[i] = NULL;
      continue;
    }

    if (i > 10 && i <= 16) {
      continue;
    }

    if (i > 21 && i <= 23) {
      continue;
    }

    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  voidPtr before[100] = { NULL };
  voidPtr after[100] = { NULL };
  int num_compacted_blocks = compact_allocation(before, after);

  print_statistics();

  assign_compacted_blocks(before, after, (voidPtr)characters, num_compacted_blocks);

  for (int i = 0; i < 24; ++i) {
    if (characters[i] != NULL) {
      printf("characters[%2d] = %p; *characters[%2d] = %c\n", i, characters[i], i, *(characters[i]));
    }
  }

  destroy_allocator();

  return;
}