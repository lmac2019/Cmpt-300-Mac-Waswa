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

  printf("..Rising to user level w/ result = %d\n", result);
}
