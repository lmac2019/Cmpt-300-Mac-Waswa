#ifndef SHELL_H
#define SHELL_H

/* Include necessary external libraries */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "macros.h"
#include "helpers.h"

/* Function prototypes */

int tokenize_command(charPtr buff, charPtr tokens[]);
void read_command(charPtr buff, charPtr tokens[], boolPtr in_background);
void execute_command(charPtr tokens[]);

#endif