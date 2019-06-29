#include "helpers.h"
#include "producer.h"
#include "consumer.h"

static bool stop_thread = false;

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
  for (int i = 0; i < args[1]; i++) {
    pthread_cancel(kid_threads[i]);
    pthread_join(kid_threads[i], NULL);
  }

  // * 9.  Print statistics

  // * 10. Cleanup any allocated memory
  
  return 0;
}