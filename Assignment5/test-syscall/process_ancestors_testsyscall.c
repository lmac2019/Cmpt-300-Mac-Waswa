#include <linux/kernel.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/syscall.h>
#include "process_ancestors_testsyscall.h"

/*
 * The number of the current syscall test
 */
static int current_syscall_test_num = 0;


/*
 * The number of tests executed
 */
static int numTests = 0;


/*
 * The number of executed tests that passed
 */
static int numTestPassed = 0;


/*
 * The number of last syscall test to fail
 */
static int last_syscall_test_num_failed = -1;


/*
 * The total number of syscall tests that failed
 */
static int num_syscall_tests_failed = 0;


/*
 * Handles testing the process_ancestors syscall
 * with an even (non-zero) size info_array
 */
void test_even_size(void) {
  printf("\nTesting even size...\n");
  
  for (long size = 2; size <= 200; size += 2) {
	  do_process_ancestors_syscall_working(size);
  }
}


/*
 * Handles testing the process_ancestors syscall
 * with an odd size info_array
 */
void test_odd_size(void) {
  printf("\nTesting odd size...\n");

  for (long size = 1; size <= 201; size += 2) {
	  do_process_ancestors_syscall_working(size);
  }
}


/*
 * Handles testing the process_ancestors syscall
 * with an zero size info_array
 */
void test_zero_size(void) {
  printf("\nTesting zero size...\n");

  for (long size = 0; size <= 200; size += 2) {
    struct processInfoPtr info_array = malloc(sizeof(struct process_info) * 0);
    long num_filled;

    do_process_ancestors_syscall_failing(info_array, 0, &num_filled, EINVAL);
    
    free(info_array);
  }
}


/*
 * Handles testing the process_ancestors syscall
 * with a negative even size info_array
 */
void test_negative_even_size(void) {
  printf("\nTesting negative even size...\n");

  for (long size = -2; size >= -200; size -= 2) {
    struct processInfoPtr info_array = malloc(sizeof(struct process_info) * size);
    long num_filled;

    do_process_ancestors_syscall_failing(info_array, size, &num_filled, EINVAL);

    free(info_array);
  }
}


/*
 * Handles testing the process_ancestors syscall
 * with a negative odd size info_array
 */
void test_negative_odd_size(void) {
  printf("\nTesting negative odd size...\n");

  for (long size = -1; size >= -201; size -= 2) {
    struct processInfoPtr info_array = malloc(sizeof(struct process_info) * size);
    long num_filled;

    do_process_ancestors_syscall_failing(info_array, size, &num_filled, EINVAL);
  
    free(info_array);
  }
}


/*
 * Handles testing the process_ancestors syscall
 * with a varying size info_array
 */
void test_mixed_sizes(void) {
  printf("\nTesting mixed sizes...\n");

  long range = 200;
  long size = 0;

  for (int count = 0; count < range; count++) {
    int sign = (rand() % 3) - 1;
    size = sign * (rand() % range);

    struct processInfoPtr info_array = malloc(sizeof(struct process_info) * size);
    long num_filled;

    if (sign == -1 || sign == 0) {
      do_process_ancestors_syscall_failing(info_array, size, &num_filled, EINVAL);
    } else {
      do_process_ancestors_syscall_working(size);
    }
    
    free(info_array);
  }
}


/*
 * Handles testing the process_ancestors syscall
 * with bad address inputs into the syscall
 */
void test_process_ancestors_bad_address(void) {
  printf("\nTesting bad address...\n");

  // Bad num_filled pointers
  long size = 10;
  struct process_info info_array[size];
	do_process_ancestors_syscall_failing(info_array, size, NULL, EFAULT);
	do_process_ancestors_syscall_failing(info_array, size, (long*)1LL, EFAULT);
	do_process_ancestors_syscall_failing(info_array, size, (long*)123456789012345689LL, EFAULT);

	// Bad info_array pointers, or read-only memory
  long num_filled;
	do_process_ancestors_syscall_failing(NULL, size, &num_filled, EFAULT);
	do_process_ancestors_syscall_failing((void*)1, size, &num_filled, EFAULT);
	do_process_ancestors_syscall_failing((void*)test_process_ancestors_bad_address, size, &num_filled, EFAULT);

  // Bad num_filled pointers
  // Bad info_array pointers, or read-only memory
  do_process_ancestors_syscall_failing(NULL, size, NULL, EFAULT);
	do_process_ancestors_syscall_failing((void*)1, size, (void*)1, EFAULT);
	do_process_ancestors_syscall_failing((void*)test_process_ancestors_bad_address, size, (void*)test_process_ancestors_bad_address, EFAULT);
}

/*
 * Handles testing the process_ancestors syscall
 * in situations where the syscall should always pass
 * 
 * size: length of info_array
 */
void do_process_ancestors_syscall_working(long size) {
  struct process_info info_array[size];

  long num_filled;

	int result = do_process_ancestors_syscall(info_array, size, &num_filled);

  for(long i = 0; i < num_filled; i++){
    printf("pid[%ld]: %ld\n", i, info_array[i].pid);
    printf("name[%ld]: %s\n", i, info_array[i].name);
    printf("state[%ld]: %ld\n", i, info_array[i].state);
    printf("uid[%ld]: %ld\n", i, info_array[i].uid);
    printf("nvscw[%ld]: %ld\n", i, info_array[i].nvcsw);
    printf("nivcsw[%ld]: %ld\n", i, info_array[i].nivcsw);
    printf("num_children[%ld]: %ld\n", i, info_array[i].num_children);
    printf("num_siblings[%ld]: %ld\n", i, info_array[i].num_siblings);
  }

	PROCESS_ANCESTORS_TEST(result == 0);
	// * Add tests here to check for matching process fields
}


/*
 * Handles testing the process_info syscall
 * in situations where the syscall should always fail
 * 
 * info_array[]: array of process_info structs 
 * size: length of data array
 * num_filled: a pointer to a variable that will contain the number of entries
 * in info_array
 * ret_code: the expected return code from the failed syscall
 */
void do_process_ancestors_syscall_failing(
  struct process_info info_array[],
  long size,
  longPtr num_filled,
  long ret_code
) {
  int result = do_process_ancestors_syscall(info_array, size, num_filled);
	PROCESS_ANCESTORS_TEST(result == ret_code);
}


/*
 * Handles actually performing the syscall
 * 
 * info_array: a pointer to an process_info struct 
 * size: length of data array
 * num_filled: a pointer to a variable that will contain the number of entries
 * in info_array
 */
int do_process_ancestors_syscall(
  struct processInfoPtr info_array, 
  long size,
  longPtr num_filled
) {
	current_syscall_test_num++;

  if (current_syscall_test_num == 1) {
    printf("Tests for process ancestors syscall\n");
  }

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
 * Prints a summary of tests passed and failed
 */
void test_process_ancestors_print_summary(void) {
  printf("\nExecution finished.\n");
  printf("%4d/%d tests passed.\n", numTestPassed, numTests);
  printf("%4d/%d tests FAILED.\n", numTests - numTestPassed, numTests);
  printf("%4d/%d unique sys-call testing configurations FAILED.\n\n", 
  num_syscall_tests_failed, current_syscall_test_num);
}


/*
 * Handles checking whether or not a test passed
 * 
 * success: a boolean indicating whether ot not a test passed
 * lineNum: an integer representing the lineNumber of the failed test
 * argStr: a pointer to a string containing a message from the failed test
 */
void process_ancestors_test_internal(bool success, int lineNum, charPtr argStr) {
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
 * Test for process_ancestors syscall
 */
void test_process_ancestors_syscall(void) {
  test_even_size();

  test_odd_size();

  test_zero_size();

  test_negative_even_size();

  test_negative_odd_size();

  test_mixed_sizes();

  test_process_ancestors_bad_address();

  test_process_ancestors_print_summary();
}