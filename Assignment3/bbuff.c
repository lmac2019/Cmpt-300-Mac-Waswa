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
 * Semaphore accounting for the number of users interacting with the buffer
 */
static sem_t bounded_buffer_mutex;

/*
 * Semaphore accounting for the amount of filled buffer slots
 */
static sem_t filled_buffer_slots;

/*
 * Semaphore accounting for the amount of empty buffer slots
 */
static sem_t empty_buffer_slots;

/*
 * Initializes bounded_buffer to be an array of pointers to -1
 * Function takes no arguments
 */
void bbuff_init (void) {
  count = 0;

  sem_init(&bounded_buffer_mutex, 0, 1);
  sem_init(&filled_buffer_slots, 0, 0);
  sem_init(&empty_buffer_slots, 0, BUFFER_SIZE);

  for (int i = 0; i < BUFFER_SIZE; i++) {
    bounded_buffer[i] = NULL;
  }
}

/*
 * Inserts an item into the bounded buffer
 * item: item to be inserted into the bounded buffer
 */
void bbuff_blocking_insert (voidPtr item) {
  sem_wait(&empty_buffer_slots);

  sem_wait(&bounded_buffer_mutex);

  if (bounded_buffer[count] != NULL) {
    free(bounded_buffer[count]);
  }

  bounded_buffer[count] = (candyStructPtr)item;

  count++;

  sem_post(&bounded_buffer_mutex);

  sem_post(&filled_buffer_slots);
}

/*
 * Extracts an item from the bounded buffer
 * Function takes no arguments
 */
voidPtr bbuff_blocking_extract (void) {
  candyStructPtr last_candy;

  sem_wait(&filled_buffer_slots);

  sem_wait(&bounded_buffer_mutex);

  last_candy = (candyStructPtr)bounded_buffer[count];

  count--;

  sem_post(&bounded_buffer_mutex);

  sem_post(&empty_buffer_slots);

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
 * Frees up memory in the bounded buffer
 */
void free_bbuff (void) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (bounded_buffer[i] != NULL) {
      free(bounded_buffer[i]);
    }
  }
}