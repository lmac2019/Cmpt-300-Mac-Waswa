#include "helpers.h"
#include "producer.h"
#include "consumer.h"

static bool stop_thread = false;

int main (int argc, charPtr* argv) {
  if (argc != 4) {
    print_error_message("Wrong number of arguments. 3 arguments expected in the form: ./candykids <#factories> <#kids> <#seconds>");
  }

  int converted_arguments[3];
  intPtr fields[3];
  for (int i = 1; i < argc; i++) {
    converted_arguments[i - 1] = atoi(argv[i]);

    if (converted_arguments[i - 1] <= 0){
      print_error_message("All arguments must be integers and must be greater than zero");
    } else {
      fields[i - 1] = &converted_arguments[i - 1];
    }
  }

  bbuff_init();

  // * Launch candy factory threads
  pthread_t factory_threads[*fields[0]];
  for (int i = 0; i < *fields[0]; i++) {
    pthread_create(&factory_threads[i], NULL, (voidPtr) produce, &i);
  }

  // * Launch kid threads
  pthread_t kid_threads[*fields[1]];
  for (int i = 0; i < *fields[1]; i++) {
    pthread_create(&kid_threads[i], NULL, (voidPtr) consume, NULL);
  }

  // * Wait for requested time
  for (int i = 1; i <= *fields[2]; i++) {
    sleep(1);
    printf("Time %ds\n", i);
  }

  // * Stop candy factory threads
  stop_thread = true;
  for (int i = 0; i < *fields[0]; i++) {
    pthread_join(factory_threads[i], NULL);
  }

  // * Wait until no more candy
  while (!bbuff_is_empty()) {
    printf("Waiting for all candy to be consumed\n");
    sleep(1);
  }

  // * Stop kid threads
  for (int i = 0; i < *fields[1]; i++) {
    pthread_cancel(kid_threads[i]);
    pthread_join(kid_threads[i], NULL);
  }
    // 9.  Print statistics
    // 10. Cleanup any allocated memory
  return 0;
}