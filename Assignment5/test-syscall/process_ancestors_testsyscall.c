#include <linux/kernel.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/syscall.h>
#include "process_ancestors_testsyscall.h"
#include "process_ancestors_testsyscall_constants.h"

/*
 * Handles testing the process_ancestors syscall
 * with an even (non-zero) size info_array
 */
void test_even_size(void) {
  for (int i = 2; i <= 12; i += 2) {
    long size = i;
	  do_syscall_working(size);
  }
}


/*
 * Handles testing the process_ancestors syscall
 * with an odd size info_array
 */
void test_odd_size(void) {
  for (int i = 1; i <= 11; i += 2) {
    long size = i;
	  do_syscall_working(size);
  }
}

/*
 * Handles testing the process_ancestors syscall
 * in situations where the syscall should always pass
 * 
 * size: length of info_array
 */
static void do_syscall_working(long size) {
  struct process_info info_array[size];
  long num_filled;

	int result = do_syscall(info_array, size, &num_filled);
	
  for(int i = 0; i < num_filled; i++){
    printf("pid: %ld\n",info_array[i].pid );
    printf("name: %s\n",info_array[i].name );
    printf("state: %ld\n",info_array[i].state );
    printf("uid: %ld\n",info_array[i].uid );
    printf("nvscw: %ld\n",info_array[i].nvcsw );
    printf("nivcsw: %ld\n",info_array[i].nivcsw );
    printf("num_children: %ld\n",info_array[i].num_children );
    printf("num_siblings: %ld\n",info_array[i].num_siblings );
  }

	TEST(result == 0);
	// * Add tests here to check for matching process fields
}

/*
 * Handles actually performing the syscall
 * 
 * info_array: a pointer to an process_info struct 
 * size: length of data array
 * num_filled: a pointer to a variable that will contain the number of entries
 * in info_array
 */
static int do_syscall(
  struct processInfoPtr info_array, 
  long size,
  longPtr num_filled
) {
	current_syscall_test_num++;

	printf("\nTest %d: ..Diving to kernel level\n", current_syscall_test_num);
	
  int result = syscall(_PROCESS_ANCESTORS_, info_array, size, num_filled);
	int my_errno = errno;
	
  printf("..Rising to user level w/ result = %d", result);
	
  if (result < 0) {
		printf(", errno = %d", my_errno);
	} else {
		my_errno = 0;
	}
  
	printf("\n");
	
  return my_errno;
}

/*
 * Handles checking whether or not a test passed
 * 
 * success: a boolean indicating whether ot not a test passed
 * lineNum: an integer representing the lineNumber of the failed test
 * argStr: a pointer to a string containing a message from the failed test
 */
static void test_internal(bool success, int lineNum, charPtr argStr) {
  numTests++;

	if (!success) {
		if (current_syscall_test_num != last_syscall_test_num_failed) {
			last_syscall_test_num_failed = current_syscall_test_num;
			num_syscall_tests_failed++;
		}
		printf("-------> ERROR %4d: test on line %d failed: %s\n",
				numTestPassed, lineNum, argStr);
	} else {
		numTestPassed++;
	}
}

/*
 * Prints a summary of tests passed and failed
 */
static void test_print_summary(void) {
  printf("\nExecution finished.\n");
  printf("%4d/%d tests passed.\n", numTestPassed, numTests);
  printf("%4d/%d tests FAILED.\n", numTests - numTestPassed, numTests);
  printf("%4d/%d unique sys-call testing configurations FAILED.\n", 
  num_syscall_tests_failed, current_syscall_test_num);
}

/*
 * Test for process_ancestors syscall
 */
void test_array_stats_syscall(void) {
  test_even_size();

  test_odd_size();

  test_zero_size();

  test_negative_even_size();

  test_negative_odd_size();

  test_print_summary();
}