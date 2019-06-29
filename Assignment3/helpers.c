#include "helpers.h"

/*
 * Handles printing an error message to the terminal 
 * and exiting the program with a -1 code
 */
void print_error_message (charPtr error_message) {
  printf("%s\n", error_message);
  exit(-1);
}