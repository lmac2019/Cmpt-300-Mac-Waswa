#include "bbuff.h"

/*
 * Buffer for storing candy
 */
static voidPtr bounded_buffer[BUFFER_SIZE];

/*
 * Number of items in the buffer
 */
static int count;

/*
 * Next empty spot in the buffer
 */
static int next_empty_index;

/*
 * Last filled spot in the buffer
 */
static int last_filled_index;

/*
 * Mutex for the bounded buffer
 */
static sem_t bounded_buffer_semaphore;

/*
 * Condition variable for threads to wait if not full and proceed otherwise
 */
static pthread_cond_t not_full;

/*
 * Condition variable for threads to wait if not empty and proceed otherwise
 */
static pthread_cond_t not_empty;

/*
 * Initializes bounded_buffer to be an array of pointers to -1
 * Function takes no arguments
 */
void bbuff_init (void) {
  count = 0;
  next_empty_index = 0;
  last_filled_index = 0;

  sem_init(&bounded_buffer_semaphore, 0, 1);
  pthread_cond_init(&not_full, NULL);
  pthread_cond_init(&not_empty, NULL);

  for (int i = 0; i < BUFFER_SIZE; i++) {
    bounded_buffer[i] = NULL;
  }
}

/*
 * Inserts an item into the bounded buffer
 * item: item to be inserted into the bounded buffer
 */
void bbuff_blocking_insert (voidPtr item) {
  sem_wait(&bounded_buffer_semaphore);

  while (bbuff_is_full()) {
    pthread_cond_wait(&not_full, &bounded_buffer_semaphore);
  }

  if (bounded_buffer[next_empty_index] != NULL) {
    free(bounded_buffer[next_empty_index]);
  }

    bounded_buffer[next_empty_index] = (candyStructPtr)item;

  next_empty_index = (next_empty_index + 1) % BUFFER_SIZE;
  count++;

  pthread_cond_signal(&not_empty);

  sem_post(&bounded_buffer_semaphore);
}

/*
 * Extracts an item from the bounded buffer
 * Function takes no arguments
 */
voidPtr bbuff_blocking_extract (void) {
  candyStructPtr last_candy;

  sem_wait(&bounded_buffer_semaphore);

  while (bbuff_is_empty()) {
    pthread_cond_wait(&not_empty, &bounded_buffer_semaphore);
  }

  last_candy = (candyStructPtr)bounded_buffer[last_filled_index];

  last_filled_index = (last_filled_index + 1) % BUFFER_SIZE;
  count--;

  pthread_cond_signal(&not_full);

  sem_post(&bounded_buffer_semaphore);

  return last_candy;
}

/*
 * Returns true if the bounded buffer is empty otherwise returns false
 * Function takes no arguments
 */
bool bbuff_is_empty(void) {
  return count == 0;
}

/*
 * Returns true if the bounded buffer is full otherwise returns false
 * Function takes no arguments
 */
bool bbuff_is_full(void) {
  return count == BUFFER_SIZE;
}

/*
 * Frees up memory in the bounded buffer
 */
void free_bbuff (void) {
  print_message("\t\t\t\t\tFreeing up memory in the bounded buffer...");

  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (bounded_buffer[i] != NULL) {
      free(bounded_buffer[i]);
    }
  }
}