#include "producer.h"

/*
 * Handles getting the current time in milliseconds
 */
static double current_time_in_ms (void) {
  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}

/*
 * Handles producing candy to be stored in the bounded buffer
 */
void produce (voidPtr arg) {
  int factory_number = *((intPtr)arg);

  while (true) {
    int sleep_time = rand() % 4;
    printf("\tFactory %d ships candy & waits %ds\n", factory_number, sleep_time);

    candyStructPtr candy = (candyStructPtr)malloc(sizeof(candy_t));
    candy->factory_number = factory_number;
    candy->time_stamp_in_ms = current_time_in_ms();
    bbuff_blocking_insert(candy);

    sleep(sleep_time);
  }

  printf("Candy-factory %d done\n", factory_number);

  return;
}