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