#ifndef HISTORY_H
#define HISTORY_H

/* Include necessary external libraries */
#include "helpers.h"
#include "macros.h"
#include <ctype.h>
#include <err.h>

/* Globals */
char history[HISTORY_DEPTH][COMMAND_LENGTH];

/* Function prototypes */
void init_history();
void add_command_to_history(char new_command_buffer[], int new_command_index);
void shift_commands();
charPtr get_command_from_history();
void print_last_ten_commands(int last_command_index);
charPtr get_last_command(int last_command_index);
bool is_history_command(char buffer[]);
bool is_previous_command(char buffer[]);
bool is_nth_command(char buffer[]);
bool has_proper_number(char buffer[]);
int get_command_index(char buffer[], int last_command_index);

#endif