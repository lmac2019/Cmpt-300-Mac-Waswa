#ifndef SHELL_H
#define SHELL_H

/* Include necessary external libraries */

#include "macros.h"
#include "helpers.h"
#include "history.h"
#include <signal.h>
#include <errno.h>

/* Function prototypes */

int tokenize_command(charPtr buff, charPtr tokens[]);
bool read_and_execute_command(charPtr buff, charPtr tokens[], boolPtr in_background, intPtr num_background_child_processes, intPtr last_command_index);
void execute_command(charPtr tokens[], const bool in_background, intPtr num_background_child_processes, int last_command_index);

#endif