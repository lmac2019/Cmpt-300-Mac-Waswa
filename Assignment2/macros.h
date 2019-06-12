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
#define CWD_LENGTH 4096
#define ERROR_CODE -1
#define WAIT_ALL_CHILDREN -1
#define EXIT_COMMAND "exit"
#define PWD_COMMAND "pwd"
#define CD_COMMAND "cd"
#define SHOW_HISTORY_COMMAND "history"
#define PREVIOUS_COMMAND "!!"
#define HISTORY_DEPTH 10

#endif