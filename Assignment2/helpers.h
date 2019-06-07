#ifndef HELPERS_H
#define HELPERS_H

/* Include necessary external libraries */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "macros.h"
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */

void write_to_shell(charPtr message);
void handle_fork_error();
void handle_child_process(charPtr tokens[]);
void handle_parent_process(const pid_t new_process_id, const bool in_background, intPtr num_background_child_processes);
void wait_foreground_child_process(const pid_t new_process_id);
void wait_background_child_processes(intPtr num_background_child_processes);

#endif
