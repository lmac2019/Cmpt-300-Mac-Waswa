#include "allocator_helpers.h"

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