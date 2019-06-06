#include "macros.h"
#include "helpers.h"

/*
 * Uses the write linux command to write a message to the shell
 * message: Character array containing string to display.
 */
void write_to_shell (charPtr message) {
  write(STDOUT_FILENO, message, strlen(message));
}