#include "consumer.h"

/*
 * Handles consuming candy from the bounded buffer
 */
void consume (void) {
  while (true) {
    candyStructPtr extracted_candy = bbuff_blocking_extract();
    
    printf(
      "Consumed candy created by factory %d at %fs", 
      extracted_candy->factory_number, 
      extracted_candy->time_stamp_in_ms
    );

    int sleep_time = rand() % 2;
    sleep(sleep_time);
  }
}