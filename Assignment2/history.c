#include "history.h"

/*
* Handles adding a new command to history
* new_command_buffer[]: an array of characters containing the new command to be added to history
* new_command_row: the index of the history array at which this new command should be added
*/
void add_command_to_history (char new_command_buffer[], int new_command_row) {
  int row = new_command_row;

  if (new_command_row >= HISTORY_DEPTH) {
    shift_commands();
    row = HISTORY_DEPTH - 1;
  } 

  int col;
  for (col = 0; new_command_buffer[col] != '\0'; col++) {
    history[row][col] = new_command_buffer[col];
  }

  history[row][col] = '\0';
}

/*
* Handles shifting the commands in the history array 
* such that the oldest command is deleted and there is room for a new command
*/
void shift_commands() {
  for (int row = 0; row < HISTORY_DEPTH - 1; row++) {
    for (int col = 0; col < COMMAND_LENGTH; col++) {
      history[row][col] = history[row + 1][col];
    }
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
  
  for (int row = 0; row < HISTORY_DEPTH && history[row][0] != '\0'; row++) {
    int command_index;
    
    if (last_command_index > HISTORY_DEPTH) {
      command_index = last_command_index - HISTORY_DEPTH + row + 1;
    } else {
      command_index = row + 1;
    }

    write_integer_to_shell(command_index);
    write_string_to_shell("\t");
    write_string_to_shell(history[row]);
    write_string_to_shell("\n");
  }
}

/*
* Gets the last command in history
* last_command_index: the index of the last command to be entered
*/
charPtr get_last_command (int last_command_index) {
  if (last_command_index == 0) {
    errx(ERROR_CODE, "Unable to execute command: No previous commands");
  }

  int command_index = HISTORY_DEPTH - 1;
  if (last_command_index < HISTORY_DEPTH) {
    command_index = last_command_index - 1;
  }

  return history[command_index];
}

/*
* Checks whether the command in the buffer is either a previous history command or nth history command
* buffer: an array of characters containing the new command to be added to history
*/
bool is_history_command (char buffer[]) {
  return buffer[0] == '!';
}

/*
* Checks whether the command in the buffer is the previous history command
* buffer: an array of characters containing the new command to be added to history
*/
bool is_previous_command (char buffer[]) {
  return strlen(buffer) == 2 && buffer[0] == '!' && buffer[1] == '!';
}