#include "helpers.h"

/*
 * Creates tokens for the given command
 * buff: Character array containing string to tokenize.
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 * in_background: pointer to a boolean variable. Set to true if user entered & after command.
 */
void create_tokens (charPtr buff, charPtr tokens[], boolPtr in_background) {
  // * Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);

	if (token_count == 0) {
		return;
	}

	// * Extract if running in background:
	if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}

/*
 * Uses the write linux command to write a string to the shell
 * message: Character array containing string to display.
 */
void write_string_to_shell (charPtr message) {
  write(STDOUT_FILENO, message, strlen(message));
}

/*
 * Allows an integer to be written to the shell
 * number: Integer to display
 */
void write_integer_to_shell (int number) {
  char stringify_number[11];
  sprintf(stringify_number, "%d", number);
  write_string_to_shell(stringify_number);
}

/*
 * Handles execution of the command in the child process
 * tokens[]: an array of character pointers containing the tokens of the command
 */
void handle_child_process (charPtr tokens[]) {
  if (execvp(tokens[0], tokens) == ERROR_CODE) {
    perror("An error occured when executing the command in the child process");
    exit(ERROR_CODE);
  }
}

/*
 * Handles waiting for child prcoesses in the parent process
 * new_process_id: process id of the child process that was just created
 * in_background: a boolean variable.
 * True if the user's command was entered as a background process.
 * False if the user's command was entered as a foreground process.
 * num_background_child_processes: a pointer to a variable containing the current number of background child processes.
 */
void handle_parent_process (const pid_t new_process_id, const bool in_background, intPtr num_background_child_processes) {
  if (in_background) {
    *num_background_child_processes += 1;
  } else {
    wait_foreground_child_process(new_process_id);
  }
  wait_background_child_processes(num_background_child_processes);
}

/*
 * Handles waiting for a foreground child prcoess.
 * Suspends execution of the parent process.
 * Waits for the foreground child process to terminate.
 * new_process_id: process id of the child process to be waited
 */
void wait_foreground_child_process (const pid_t new_process_id) {
  int status;
  do {
    int wait_result = waitpid(new_process_id, &status, 0);
    if (wait_result == ERROR_CODE) {
      perror("An error occured when waiting for the child process");
      exit(ERROR_CODE);
    }
  } while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

/*
 * Handles waiting for all background child processes
 * If no child background process has terminated then immediately returns
 * If one child background process has terminated then its resources are cleaned up
 * and the reminaing background child processes are waited
 * num_background_child_processes: a pointer to a variable containing the current number of background child processes.
 */
void wait_background_child_processes (intPtr num_background_child_processes) {
  int wait_result;
  if (*num_background_child_processes > 0) {
    do {
      wait_result = waitpid(WAIT_ALL_CHILDREN, NULL, WNOHANG);
      if (wait_result == ERROR_CODE) {
        perror("An error occured in waiting for all child processes");
        exit(ERROR_CODE);
      } else if (wait_result > 0) {
        *num_background_child_processes -= 1;
      }
    } while (*num_background_child_processes > 0 && wait_result > 0);
  }
}

/*
 * Handles the execution of internal commands
 * tokens[]: an array of character pointers containing the tokens of the command
 */
bool handle_internal_commands (charPtr tokens[]) {
  for (int i = 0; tokens[i] != NULL; i++) {
    if (strcmp(EXIT_COMMAND, tokens[i]) == 0) {
			exit(0);
		}
  }

  for (int i = 0; tokens[i] != NULL; i++) {
    if (strcmp(PWD_COMMAND, tokens[i]) == 0) {
      char path[CWD_LENGTH];
      charPtr cwd = getcwd(path, CWD_LENGTH);

      if (cwd == NULL) {
        perror("An error occured when executing the getcwd() function");
      } else {
        write_string_to_shell(cwd);
        write_string_to_shell("\n");
      }

      return true;
    }
  }

  for (int i = 0; tokens[i] != NULL; i++) {
    if (strcmp(CD_COMMAND, tokens[i]) == 0) {
      if (i == 0) {
        if (chdir(tokens[i + 1]) == ERROR_CODE) {
          perror("An error occured when executing the chdir() function");
        }
      }

      return true;
    }
  }

  return false;
}

/*
 * Handles the execution of the show history command
 * tokens[]: an array of character pointers containing the tokens of the command
 * last_command_index: the index of the last command to be entered
 */
bool handle_show_history_command (charPtr tokens[], int last_command_index) {
  if (strcmp(tokens[0], SHOW_HISTORY_COMMAND) == 0) {
    print_last_ten_commands(last_command_index);
    return true;
  }

  return false;
}

/* 
 * Handles all kinds of history commands
 * buffer[]: an array of characters containing a history command
 * tokens[]: an array of character pointers containing the tokens of the command
 * in_background: pointer to a boolean variable. Set to true if user entered.
 * num_background_child_processes: a pointer to a variable containing the current number of background child processes.
 * last_command_index: a pointer to the the index of the last command to be entered
 */
void handle_history_commands (char buffer[], charPtr tokens[], boolPtr in_background, intPtr num_background_child_processes, intPtr last_command_index) {
  if (is_previous_command(buffer)) {
    return handle_previous_history_command(tokens, in_background, num_background_child_processes, last_command_index);
  } else if (is_nth_command(buffer)) {
    int command_index = get_command_index(buffer, *last_command_index);
    if (command_index == ERROR_CODE) {
      warnx("Unable to execute command: Invalid command number");
      return;
    } else {
      return handle_nth_history_command(command_index, tokens, in_background, num_background_child_processes, last_command_index);
    }
  } else {
    warnx("Unable to execute command: Invalid history command");
  }
}

/* 
 * Handles executing the previous history command
 * This command executes the previous command in history if it exists
 * And adds the command to the end of the history 2D array
 * tokens[]: an array of character pointers containing the tokens of the command
 * in_background: pointer to a boolean variable. Set to true if user entered.
 * num_background_child_processes: a pointer to a variable containing the current number of background child processes.
 * last_command_index: a pointer to the the index of the last command to be entered
 */
void handle_previous_history_command (charPtr tokens[], boolPtr in_background, intPtr num_background_child_processes, intPtr last_command_index) {
  if (*last_command_index == 0) {
    warnx("Unable to execute command: No previous commands");
    return;
  } 

  int previous_command_index = HISTORY_DEPTH - 1;
  if (*last_command_index < HISTORY_DEPTH) {
    previous_command_index = *last_command_index - 1;
  }

  add_command_to_history(history[previous_command_index], *last_command_index);

  char buffer_copy[COMMAND_LENGTH];
  memcpy(buffer_copy, &history[previous_command_index], COMMAND_LENGTH - 1);
  buffer_copy[COMMAND_LENGTH - 1] = '\0';
  create_tokens(buffer_copy, tokens, in_background);

  *last_command_index += 1;

  write_string_to_shell(history[previous_command_index]);
  write_string_to_shell("\n");

  execute_command(tokens, *in_background, num_background_child_processes, *last_command_index);
}

/* 
 * Handles executing the nth history command
 * This command executes the nth command in history if it exists
 * And adds the command to the end of the history 2D array
 * command_index: the index of the command in history
 * tokens[]: an array of character pointers containing the tokens of the command
 * in_background: pointer to a boolean variable. Set to true if user entered.
 * num_background_child_processes: a pointer to a variable containing the current number of background child processes.
 * last_command_index: a pointer to the the index of the last command to be entered
 */
void handle_nth_history_command (int command_index, charPtr tokens[], boolPtr in_background, intPtr num_background_child_processes, intPtr last_command_index) {
  if (*last_command_index == 0) {
    warnx("Unable to execute command: No commands found");
    return;
  }

  char buffer_copy[COMMAND_LENGTH];
  memcpy(buffer_copy, &history[command_index], COMMAND_LENGTH - 1);
  buffer_copy[COMMAND_LENGTH - 1] = '\0';
  create_tokens(buffer_copy, tokens, in_background);

  char second_buffer_copy[COMMAND_LENGTH];
  memcpy(second_buffer_copy, &history[command_index], COMMAND_LENGTH - 1);
  second_buffer_copy[COMMAND_LENGTH - 1] = '\0';

  add_command_to_history(second_buffer_copy, *last_command_index);

  *last_command_index += 1;

  write_string_to_shell(second_buffer_copy);
  write_string_to_shell("\n");

  execute_command(tokens, *in_background, num_background_child_processes, *last_command_index);
}

/*
 * Handles printing the prompt for the user to type
 */
void print_prompt() {
  char path[CWD_LENGTH];
  getcwd(path, CWD_LENGTH);
  write_string_to_shell(path);
  write_string_to_shell("> ");
}