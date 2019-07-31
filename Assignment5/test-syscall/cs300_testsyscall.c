#include "cs300_testsyscall.h"

#define _CS300_TEST_ 340

/*
 * Test for cs300_test syscall
 */
void test_cs300_test_syscall(void) {
  printf("\nDiving to kernel level\n\n");

  int result = syscall(_CS300_TEST_, 12345);

  printf("\nRising to user level w/ result = %d\n\n", result);
}