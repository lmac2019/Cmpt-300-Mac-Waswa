#include "shell.h"

/*
 * Command Input and Processing
 */

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 * Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 * Will be modified so tokens[i] points to the i'th token
 * in the string buff. All returned tokens will be non-empty.
 * NOTE: pointers in tokens[] will all point into buff!
 * Ends with a null pointer.
 * returns: number of tokens.
 */
int tokenize_command (charPtr buff, charPtr tokens[]) {
	int token_count = 0;
	bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);

	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
      // * Handle token delimiters (ends):
      case ' ':
      case '\t':
      case '\n': {
        buff[i] = '\0';
        in_token = false;
        break;
      }

      // * Handle other characters (may be start)
      default: {
        if (!in_token) {
          tokens[token_count] = &buff[i];
          token_count++;
          in_token = true;
        }
      }
		}
	}

	tokens[token_count] = NULL;

	return token_count;
}

/*
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. 
 * Must be at least NUM_TOKENS long. Will strip out up to one final '&' token.
 * Tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered.
 * an & as their last token; otherwise set to false.
 */
void read_command (charPtr buff, charPtr tokens[], boolPtr in_background) {
	*in_background = false;

	// * Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH - 1);
  if (length < 0) {
		perror("Unable to read command from keyboard. Terminating.\n");
		exit(-1);
	}

	// * Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

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
 * Uses the tokens that have been created from the user's command
 * to execute the command through a child process.
 * tokens[]: an array of character pointers containing the tokens of the command
 * in_background: a boolean variable. 
 * True if the user's command was entered as a background process.
 * False if the user's command was entered as a foreground process.
 */
void execute_command (const charPtr tokens[], const bool in_background) {
  pid_t new_process_id = fork();

  if (new_process_id < 0) {
    // * Failed to create child process
    perror("An error occured when creating a child process");
    exit(-1);
  } else if (new_process_id == 0) {
    // * Child process enters here
    // * Execute command in child process
    if (execvp(tokens[0], tokens) == -1) {
      // * Error encountered in execution of command by child process
      perror("An error occured when executing the command in the child process");
      exit(-1);
    }
  } else {
    // * Parent process enters here
    if (!in_background) {
      // * Foreground process
      // * Suspend execution of parent process and wait for child process to terminate
      int status;
      do {
        int wait_result = waitpid(new_process_id, &status, WNOHANG);
        if (wait_result == -1) {
          perror("An error occured in waiting for the child process");
          exit(-1);
        }
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    // * Clean up any previously exited background processes
    while (waitpid(-1, NULL, WNOHANG) > 0);
  }
}

/*
 * Main and Execute Commands
 */
int main (int argc, charPtr argv[]) {
	char input_buffer[COMMAND_LENGTH];
	charPtr tokens[NUM_TOKENS];

	while (true) {
		// * Get command
		// * Use write because we need to use read() to work with
		// * signals, and read() is incompatible with printf().
		write_to_shell("> ");
		bool in_background = false;
    read_command(input_buffer, tokens, &in_background);
    execute_command(tokens, in_background);

		// * DEBUG: Dump out arguments:
		for (int i = 0; tokens[i] != NULL; i++) {
      if (strcmp("exit", tokens[i]) == 0) {
        exit(0);
      }

      write_to_shell("   Token: ");
      write_to_shell(tokens[i]);
      write_to_shell("\n");
		}

		if (in_background) {
      write_to_shell("Run in background.");
    }

		/*
		 * Steps For Basic Shell:
		 * 1. Fork a child process
		 * 2. Child process invokes execvp() using results in token array.
		 * 3. If in_background is false, parent waits for child to finish. 
     * Otherwise, parent loops back to read_command() again immediately.
		 */
	}

	return 0;
}