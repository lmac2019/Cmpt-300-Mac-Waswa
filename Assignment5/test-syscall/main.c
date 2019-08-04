#include "cs300_testsyscall.h"
#include "array_stats_testsyscall.h"
#include "process_ancestors_testsyscall.h"

int main (int argc, char* argv[]) {
  // * Test for cs300_test syscall
 test_cs300_test_syscall();

  // * Test for array_stats syscall
  // test_array_stats_syscall();

  test_process_ancestors_syscall();

  test_process_ancestors_syscall_exception();

  return 0;
}