#ifndef SHELL_H
#define SHELL_H

/* Include necessary external libraries */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Include macros */

#define charPtr char*
#define boolPtr bool*
#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)

/* Function prototypes */

int tokenize_command(charPtr buff, charPtr tokens[]);
void read_command(charPtr buff, charPtr tokens[], boolPtr in_background);

#endif