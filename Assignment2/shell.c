#include "shell.h"

/*
 * Command Input and Processing
 */

/*
 * Global variables
 */

static int last_command_index = 0;

/*
 * Handler for SIGINT signal (CTRL + C)
 */
void handle_SIGINT() {
  write_string_to_shell("\n");
  print_last_ten_commands(last_command_index);
  print_prompt();
}

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
 * last_command_index: the index of the last command to be entered
 * an & as their last token; otherwise set to false.
 */
void read_command (charPtr buff, charPtr tokens[], boolPtr in_background, int last_command_index) {
	*in_background = false;

	// * Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH - 1);
  if ((length < 0) && (errno != EINTR)) {
		perror("Unable to read command from keyboard. Terminating.\n");
		exit(ERROR_CODE);
	}

	// * Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
  }

  charPtr buffer_to_tokenize = buff;
  if (is_history_command(buffer_to_tokenize)) {
    if (is_previous_command(buffer_to_tokenize)) {
      buffer_to_tokenize = get_last_command(last_command_index);
      write_string_to_shell(buffer_to_tokenize);
      write_string_to_shell("\n");
      add_command_to_history(buffer_to_tokenize, last_command_index);
    } else if (is_nth_command(buffer_to_tokenize)) {
      int command_index = get_command_index(buffer_to_tokenize, last_command_index);
      write_string_to_shell(history[command_index]);
      write_string_to_shell("\n");

      if (last_command_index >= HISTORY_DEPTH) {
        add_command_to_history(history[command_index - 1], last_command_index);
        buffer_to_tokenize = history[command_index - 1];
      } else {
        buffer_to_tokenize = history[command_index];
        add_command_to_history(history[command_index], last_command_index);
      }
    } else {
      errx(ERROR_CODE, "Unable to execute command: Invalid history command");
    }
  } else {
    add_command_to_history(buffer_to_tokenize, last_command_index);
  }

  // * Tokenize (saving original command string)
	int token_count = tokenize_command(buffer_to_tokenize, tokens);
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
 * num_background_child_processes: a pointer to a variable containing the current number of background child processes.
 * last_command_index: the index of the last command to be entered
 */
void execute_command (charPtr tokens[], const bool in_background, intPtr num_background_child_processes, int last_command_index) {
  if (tokens[0] == NULL) {
		return;
	}

  if (handle_show_history_command(tokens, last_command_index)) {
    return;
  }

  if (handle_internal_commands(tokens)){
		return;
	}

  pid_t new_process_id = fork();

  if (new_process_id == ERROR_CODE) {
    handle_fork_error();
  } else if (new_process_id == 0) {
    handle_child_process(tokens);
  } else {
    handle_parent_process(new_process_id, in_background, num_background_child_processes);
  }
}

/*
 * Main and Execute Commands
 */
int main (int argc, charPtr argv[]) {
  struct sigaction handler;
  handler.sa_handler = handle_SIGINT;
  handler.sa_flags = 0;
  sigemptyset(&handler.sa_mask);
  sigaction(SIGINT, &handler, NULL);

  char input_buffer[COMMAND_LENGTH];
	charPtr tokens[NUM_TOKENS];
  int num_background_child_processes = 0;

	while (true) {
		print_prompt();

		bool in_background = false;

    read_command(input_buffer, tokens, &in_background, last_command_index);

    last_command_index++;

    execute_command(tokens, in_background, &num_background_child_processes, last_command_index);
	}

	return 0;
}