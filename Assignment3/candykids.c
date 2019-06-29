#include "helpers.h"
#include <unistd.h>

static bool stop_thread = false;

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

  while (!stop_thread) {
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

/*
 * Handles consuming candy from the bounded buffer
 */
void consume (void) {
  while (true) {
    candyStructPtr extracted_candy = (candyStructPtr)bbuff_blocking_extract();
    
    printf(
      "Consumed candy created by factory %d at %fs\n", 
      extracted_candy->factory_number, 
      extracted_candy->time_stamp_in_ms
    );

    int sleep_time = rand() % 2;
    sleep(sleep_time);
  }

  return;
}

int main (int argc, charPtr* argv) {
  // * 1. Extract arguments
  if (argc != 4) {
    print_error_message("Wrong number of arguments. 3 arguments expected in the form: ./candykids <#factories> <#kids> <#seconds>");
  }

  int args[3];
  for (int i = 1; i < argc; i++) {
    args[i - 1] = atoi(argv[i]);

    if (args[i - 1] <= 0){
      print_error_message("All arguments must be integers and must be greater than zero");
    } 
  }

  // * 2. Initialize modules
  bbuff_init();

  // * 3. Launch factory threads
  pthread_t factory_threads[args[0]];
  int factory_number[args[0]];
  for (int i = 0; i < args[0]; i++) {
    factory_number[i] = i;
  }
  for (int i = 0; i < args[0]; i++) {
    pthread_create(&factory_threads[i], NULL, (voidPtr) produce, &factory_number[i]);
  }

  // * 4. Launch kid threads
  pthread_t kid_threads[args[1]];
  for (int i = 0; i < args[1]; i++) {
    pthread_create(&kid_threads[i], NULL, (voidPtr) consume, NULL);
  }

  // * 5. Wait for requested time
  for (int i = 1; i <= args[2]; i++) {
    sleep(1);
    printf("Time %ds\n", i);
  }

  // * 6. Stop factory threads
  stop_thread = true;
  for (int i = 0; i < args[0]; i++) {
    pthread_join(factory_threads[i], NULL);
  }

  // * 7. Wait until no more candy
  while (!bbuff_is_empty()) {
    print_message("Waiting for all candy to be consumed");
    sleep(1);
  }

  // * 8. Stop kid threads
  // * Bugs when it comes to destroying kid threads
  for (int i = 0; i < args[1]; i++) {
    pthread_cancel(kid_threads[i]);
    pthread_join(kid_threads[i], NULL);
  }

  // * 9.  Print statistics

  // * 10. Cleanup any allocated memory
  free_bbuff();

  return 0;
}