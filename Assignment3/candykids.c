#include <stdlib.h>
#include <stdio.h>

int main (int argc, char** argv){
  //part 1 error checking
  if(argc != 4){
    printf("wrong argc number\n");
    exit(-1);
  }
  for(int i = 1; i <argc; i++){
    if(atoi(argv[i])<=0){
      printf("argv[%d]: %s wrong argv\n",i,argv[i]);
      exit(-1);
    }
    printf("%s\n", argv[i]);
  }

  // 1.  Extract arguments
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
}
