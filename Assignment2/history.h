#ifndef HISTORY_H
#define HISTORY_H

/* Include necessary external libraries */
#include "helpers.h"
#include "macros.h"

/* Globals */
char history[HISTORY_DEPTH][COMMAND_LENGTH];

/* Function prototypes */
void add_command_to_history(char new_command_buffer[], int new_command_index);
void shift_commands();
charPtr get_command_from_history();
void print_last_ten_commands(int last_command_index);

#endif