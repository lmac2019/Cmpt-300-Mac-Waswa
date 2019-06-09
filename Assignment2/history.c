#include "history.h"

/*
* Handles initialzing the history two dimensional array
*/
void init_history () {
  for (int current_row = 0; current_row < HISTORY_DEPTH; current_row++) {
    history[current_row] = malloc(COMMAND_LENGTH * sizeof(char));
  }
}

/*
* Handles adding a new command to history
* new_command_buffer[]: an array of characters containing the new command to be added to history
* new_command_index: the index of the history array at which this new command should be added
*/
void add_command_to_history (char new_command_buffer[], int new_command_index) {
  char copy_buffer[strlen(new_command_buffer)];
  strcpy(copy_buffer, new_command_buffer);

  if (new_command_index == HISTORY_DEPTH) {
    shift_commands();
    history[new_command_index - 1] = copy_buffer;
  } else {
    history[new_command_index] = copy_buffer;
  }

}

/*
* Handles shifting the commands in the history array to the left by one
*/
void shift_commands() {
  for (int current_index = 0; current_index < HISTORY_DEPTH - 1; current_index++) {
    history[current_index] = history[current_index + 1];
  }
}

/*
* Handles printing the last ten commands in history
* last_command_index: the index of the last command to be entered
*/
void print_last_ten_commands (int last_command_index) {
  if (last_command_index == 0) {
    return;
  }
  
  for (int current_index = 0; current_index < HISTORY_DEPTH; current_index++) {
    int print_index = last_command_index - HISTORY_DEPTH + current_index + 1;
    // write_to_shell(print_index);
    write_to_shell("\t");
    write_to_shell(history[current_index]);
    write_to_shell("\n");
  }
}