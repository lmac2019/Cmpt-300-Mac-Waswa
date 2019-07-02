#include "helpers.h"

/*
 * Handles printing an message to the terminal 
 */
void print_message (charPtr message) {
  printf("%s\n", message);
}

/*
 * Handles printing an error message to the terminal 
 * and exiting the program with a -1 code
 */
void print_error_message (charPtr error_message) {
  print_message(error_message);
  exit(-1);
}