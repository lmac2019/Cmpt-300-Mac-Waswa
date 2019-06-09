#include "helpers.h"

/*
 * Uses the write linux command to write a message to the shell
 * message: Character array containing string to display.
 */
void write_to_shell (charPtr message) {
  write(STDOUT_FILENO, message, strlen(message));
}

/*
 * Handles displaying an error message if an error occurs when fork is used
 * message: Character array containing string to display.
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
 */
void handle_internal_commands (charPtr tokens[]) {
  for (int i = 0; tokens[i] != NULL; i++) {

		if (strcmp(EXIT_COMMAND, tokens[i]) == 0) {

			exit(0);

		} else if (strcmp(PWD_COMMAND, tokens[i]) == 0) {

      char path[4096];
      charPtr cwd = getcwd(path, 4096);
      
      if (cwd == NULL) {
        perror("An error occured when executing the getcwd() function");
      } else {
        write_to_shell(cwd);
      }

      return;

    } else if (strcmp(CD_COMMAND, tokens[i]) == 0) {

      if (chdir(tokens[1]) == -1) {
        perror("An error occured whne executing the chdir() function");
      }

      return;

    }
  }
}