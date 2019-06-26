#include "bbuff.h"
#include <stdio.h>

voidPtr bounded_buffer[BUFFER_SIZE];
int last_entry_index = -1;

/*
 * Initializes bounded_buffer to be an array of pointers to -1
 * Function takes no arguments
 */
void bbuff_init (void) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    struct candyStructPtr ptr = (struct candyStructPtr) malloc(sizeof(struct candyStruct));
    ptr->factory_number = -1;
    ptr->time_stamp_in_ms = -1;
    bounded_buffer[i] = ptr;
  }
}

/*
 * Inserts an item into the bounded buffer if space is available
 * item: item to be inserted into the bounded buffer
 */
void bbuff_blocking_insert (voidPtr item) {
  if (bbuff_is_full()) {
    return;
  }

  last_entry_index++;
  ((struct candyStructPtr)bounded_buffer[last_entry_index])->factory_number = ((struct candyStructPtr)item)->factory_number;
  ((struct candyStructPtr)bounded_buffer[last_entry_index])->time_stamp_in_ms = ((struct candyStructPtr)item)->time_stamp_in_ms;
}

voidPtr bbuff_blocking_extract (void) {
  if (bbuff_is_empty()) {
    return bounded_buffer[0];
  }

  ((struct candyStructPtr)bounded_buffer[last_entry_index])->factory_number = -1;
  ((struct candyStructPtr)bounded_buffer[last_entry_index])->time_stamp_in_ms = -1;
  last_entry_index--;

  return bounded_buffer[last_entry_index];
}

/*
 * Returns true if the bounded buffer is empty otherwise returns false
 * Function takes no arguments
 */
bool bbuff_is_empty(void) {
  return last_entry_index == -1;
}

/*
 * Returns true if the bounded buffer is full otherwise returns false
 * Functiont takes no arguments
 */
bool bbuff_is_full(void) {
  return last_entry_index = BUFFER_SIZE - 1;
}