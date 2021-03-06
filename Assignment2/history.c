#include "history.h"

/*
* Initializes history to an array of null terminated entries
*/
void init_history () {
  for (int row = 0; row < HISTORY_DEPTH; row++) {
    for (int col = 0; col < COMMAND_LENGTH; col++) {
      history[row][col] = '\0';
    }
  }
}

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
    write_string_to_shell("Unable to execute command: No commands in history\n");
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
  return strlen(buffer) == 2 && buffer[1] == '!';
}

/*
* Checks whether the command in the buffer is the nth history command
* buffer: an array of characters containing the new command to be added to history
*/
bool is_nth_command (char buffer[]) {
  char sub_buffer[strlen(buffer)];
  memcpy(sub_buffer, &buffer[1], strlen(buffer) - 1);
  sub_buffer[strlen(buffer) - 1] = '\0';

  if (sub_buffer[0] == '0') {
    return false;
  }

  for (int index = 0; sub_buffer[index] != '\0'; index++) {
    if (!isdigit(sub_buffer[index])) {
      return false;
    }
  }

  return true;
}

/*
* Returns the index of the nth command 
* buffer: an array of characters containing only numbers
* last_command_index: the index of the last command to be entered
*/
int get_command_index (char buffer[], int last_command_index) {
  int first_command_index = last_command_index - HISTORY_DEPTH + 1;
  if (last_command_index < HISTORY_DEPTH) {
    first_command_index = 1;
  }

  char sub_buffer[strlen(buffer)];
  memcpy(sub_buffer, &buffer[1], strlen(buffer) - 1);
  sub_buffer[strlen(buffer) - 1] = '\0';
  int command_number = atoi(sub_buffer);
  
  if (command_number > last_command_index || command_number < first_command_index) {
    return ERROR_CODE;
  }

  if (last_command_index > HISTORY_DEPTH) {
    int difference = last_command_index - command_number;
    return HISTORY_DEPTH - difference - 1;
  } else {
    return command_number - 1;
  }
}