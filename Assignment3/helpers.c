#include "helpers.h"

/*
 * Handles printing an error message to the terminal 
 * and exiting the program with a -1 code
 */
void print_error_message (charPtr error_message) {
  printf("%s\n", error_message);
  exit(-1);
}

/*
 * Handles getting the current time in milliseconds
 */
double current_time_in_ms (void) {
  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}