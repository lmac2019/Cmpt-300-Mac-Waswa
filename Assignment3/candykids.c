#include "helpers.h"
#include "bbuff.h"

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
  
    // 2.  Initialize modules
    // 3.  Launch candy-factory threads
    // 4.  Launch kid threads
    // 5.  Wait for requested time
    // 6.  Stop candy-factory threads
    // 7.  Wait until no more candy
    // 8.  Stop kid threads
    // 9.  Print statistics
    // 10. Cleanup any allocated memory

  // // Spawn thread
  //  pthread_id daThreadId;
  //  pthread_create(&daThreadId, ...)
  //
  //  // Wait
  //  sleep(...)
  //
  //  // Tell thread to stop itself, and then wait until it's done.
  //  stop_thread = true;
  //  pthread_join(daThreadID, NULL)
  return 0;
}