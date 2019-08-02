#include <linux/kernel.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/syscall.h>
#include "process_ancestors_testsyscall.h"



void test_process_ancestors_syscall(void){

  long size = 2;
  long *num = 0;

  struct process_info *process;


  int result = syscall(_PROCESS_ANCESTORS_, process, size, num);

  for(int i = 0; i< size;i++){
    printf("pid: %ld\n",process[i].pid );
    printf("name: %s\n",process[i].name );
    printf("state: %ld\n",process[i].state );
    printf("uid: %ld\n",process[i].uid );
    printf("nvscw: %ld\n",process[i].nvcsw );
    printf("nivcsw: %ld\n",process[i].nivcsw );
    printf("num_children: %ld\n",process[i].num_children );
    printf("num_siblings: %ld\n",process[i].num_siblings );
  }

  printf("..Rising to user level w/ result = %d\n", result);
}
