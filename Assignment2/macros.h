#ifndef MACROS_H
#define MACROS_H

/* Include necessary external libraries */

#include <stdbool.h>

/* Macros */

#define boolPtr bool *
#define charPtr char *
#define intPtr int *
#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
#define ERROR_CODE -1
#define WAIT_ALL_CHILDREN -1

#endif