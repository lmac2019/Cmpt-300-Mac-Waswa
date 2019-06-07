#ifndef SHELL_H
#define SHELL_H

/* Include necessary external libraries */

#include "macros.h"
#include "helpers.h"

/* Function prototypes */

int tokenize_command(charPtr buff, charPtr tokens[]);
void read_command(charPtr buff, charPtr tokens[], boolPtr in_background);
void execute_command(charPtr tokens[], const bool in_background, intPtr num_background_child_processes);

#endif