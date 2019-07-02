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
 * Next index to add candy
 */
static int next_empty_index;

/*
 * Last index to contain candy
 */
static int last_filled_index;

/*
 * Bounded buffer lock
 */
static pthread_mutex_t bounded_buffer_mutex;

/*
 * Condition variable checking that the bounded buffer is not full
 */
static pthread_cond_t not_full;

/*
 * Condition variable checking that the bounded buffer is not empty
 */
static pthread_cond_t not_empty;

/*
 * Handles unlocing a mutex after a thread's resources have been cleaned up
 * mutex: The mutex to be unlocked
 */
static void cleanup_handler(voidPtr mutex) {
  pthread_mutex_unlock(mutex);
}

/*
 * Initializes bounded_buffer to be an array of pointers to -1
 * Function takes no arguments
 */
void bbuff_init (void) {
  count = 0;
  next_empty_index = 0;
  last_filled_index = 0;

  pthread_mutex_init(&bounded_buffer_mutex, NULL);
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
  pthread_cleanup_push(cleanup_handler, &bounded_buffer_mutex);

  pthread_mutex_lock(&bounded_buffer_mutex);

  while (bbuff_is_full()) {
    pthread_cond_wait(&not_full, &bounded_buffer_mutex);
  }

  if (bounded_buffer[next_empty_index] != NULL) {
    free(bounded_buffer[next_empty_index]);
  }

  bounded_buffer[next_empty_index] = (candyStructPtr)item;
  next_empty_index = (next_empty_index + 1) % BUFFER_SIZE;

  count++;

  pthread_cond_signal(&not_empty);

  pthread_mutex_unlock(&bounded_buffer_mutex);

  pthread_cleanup_pop(0);
}

/*
 * Extracts an item from the bounded buffer
 * Function takes no arguments
 */
voidPtr bbuff_blocking_extract (void) {
  candyStructPtr last_candy;
  
  pthread_cleanup_push(cleanup_handler, &bounded_buffer_mutex);

  pthread_mutex_lock(&bounded_buffer_mutex);

  while (bbuff_is_empty()) {
    pthread_cond_wait(&not_empty, &bounded_buffer_mutex);
  }

  last_candy = (candyStructPtr)bounded_buffer[last_filled_index];
  last_filled_index = (last_filled_index + 1) % BUFFER_SIZE;

  count--;

  pthread_cond_signal(&not_full);

  pthread_mutex_unlock(&bounded_buffer_mutex);

  pthread_cleanup_pop(0);

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
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (bounded_buffer[i] != NULL) {
      free(bounded_buffer[i]);
    }
  }
}