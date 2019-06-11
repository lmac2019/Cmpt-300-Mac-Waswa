#include "helpers.h"

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
 * Handles displaying an error message if an error occurs when fork is used
 */
void handle_fork_error () {
  perror("An error occured when creating a child process");
  exit(ERROR_CODE);
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
 * last_command_index: the index of the last command to be entered
 */
void handle_history_commands (char buffer[], charPtr tokens[], boolPtr in_background, intPtr num_background_child_processes, int last_command_index) {
  if (is_previous_command(buffer)) {
    return;
  } else if (is_nth_command(buffer)) {
    return;
  } else {
    errx(ERROR_CODE, "Unable to execute command: Invalid history command");
  }
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