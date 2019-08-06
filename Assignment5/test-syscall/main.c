#include "cs300_testsyscall.h"
#include "array_stats_testsyscall.h"
#include "process_ancestors_testsyscall.h"

int main (int argc, char* argv[]) {
  // * Test for cs300_test syscall
  test_cs300_test_syscall();

  // * Test for array_stats syscall
  test_array_stats_syscall();

  // * Test for process_ancestors syscall
  test_process_ancestors_syscall();

  return 0;
}