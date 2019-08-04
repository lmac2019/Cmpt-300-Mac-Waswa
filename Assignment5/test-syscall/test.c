#include <stdio.h>
#include "test.h"

/*
 * Handles checking whether or not a test passed
 * 
 * success: a boolean indicating whether ot not a test passed
 * lineNum: an integer representing the lineNumber of the failed test
 * argStr: a pointer to a string containing a message from the failed test
 */
void test_internal(bool success, int lineNum, charPtr argStr) {
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
 * Handles resetting global variables
 */
void reset() {
  current_syscall_test_num = 0;
  numTests = 0;
  numTestPassed = 0;
  last_syscall_test_num_failed = -1;
  num_syscall_tests_failed = 0;
}