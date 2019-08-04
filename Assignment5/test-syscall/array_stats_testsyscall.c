#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/syscall.h>
#include "array_stats_testsyscall_constants.h"
#include "array_stats_testsyscall.h"


/*
 * Handles testing the array_stats syscall
 * with an array of a few positive long integers
 */
void test_positive_few(void) {
	do_syscall_working((long[]){1}, 1);
	do_syscall_working((long[]){1, 2}, 2);
	do_syscall_working((long[]){1, 2, 3}, 3);
	do_syscall_working((long[]){0, 2, 4, 6}, 4);
	do_syscall_working((long[]){5, 3, 4, 1}, 4);
}


/*
 * Handles testing the array_stats syscall
 * with an array of a few negative long integers
 */
void test_negative_few(void) {
  do_syscall_working((long[]){-1}, 1);
	do_syscall_working((long[]){-1, -2}, 2);
	do_syscall_working((long[]){-1, 2, 3}, 3);
	do_syscall_working((long[]){0, -2, 4, -6}, 4);
}


/*
 * Handles testing the array_stats syscall
 * with a large array of a both positive and negative long integers
 */
void test_many(void) {
  for (int i = 1; i <= 5; i++) {
		long size = MEG * i;
		long *data = malloc(sizeof(data[0]) * size);
		fill(data, size);
		do_syscall_working(data, size);
		free(data);
	}
}


/*
 * Handles filling data with random long integers
 * such that positive integers are at odd indices
 * and negative integers are at even indices
 * 
 * data[]: empty array to be filled
 * size: length of data array
 */
void fill(long data[], long size) {
	for (int i = 0; i < size; i++) {
		data[i] = rand();
		if (i % 2 == 0) {
			data[i] *= -1;
		}
	}
}


/*
 * Handles testing the array_stats syscall
 * where invalid arguments are paseed to the syscall
 */
void test_bad_addr(void) {
  struct array_stats stats;

	// 0 or negative sizes
	do_syscall_failing(&stats, (long[]){1}, 0, EINVAL);
	do_syscall_failing(&stats, (long[]){1}, -1, EINVAL);
	do_syscall_failing(&stats, (long[]){1}, -10000, EINVAL);

	// Bad data pointers
	do_syscall_failing(&stats, NULL, 1, EFAULT);
	do_syscall_failing(&stats, (long*)1LL, 1, EFAULT);
	do_syscall_failing(&stats, (long*)123456789012345689LL, 1, EFAULT);

	// Bad size (read off end)
	do_syscall_failing(&stats, (long[]){1}, 10*MEG, EFAULT);

	// Bad stats pointers, or read-only memory
	do_syscall_failing(NULL, (long[]){1}, 1, EFAULT);
	do_syscall_failing((void*)1, (long[]){1}, 1, EFAULT);
	do_syscall_failing((void*)test_bad_addr, (long[]){1}, 1, EFAULT);
}


/*
 * Handles testing the array_stats syscall
 * in situations where the syscall should always pass
 * 
 * data[]: array containing long integers
 * size: length of data array
 */
static void do_syscall_working(long data[], long size) {
  struct array_stats stats;

	int result = do_syscall(&stats, data, size);
	printf("Stats: min = %ld, max = %ld, sum = %ld\n",
    stats.min, stats.max, stats.sum);

	TEST(result == 0);
	TEST(stats.min == find_min(data, size));
	TEST(stats.max == find_max(data, size));
	TEST(stats.sum == find_sum(data, size));
}


/*
 * Finds the min of the entries in data
 * 
 * data[]: array containing long integers
 * size: length of data array
 */
static long find_min(long data[], long size) {
	long min = data[0];
	for (int i = 0; i < size; i++) {
		if (data[i] < min) {
			min = data[i];
		}
	}
	return min;
}


/*
 * Finds the max of the entries in data
 * 
 * data[]: array containing long integers
 * size: length of data array
 */
static long find_max(long data[], long size) {
	long max = data[0];
	for (int i = 0; i < size; i++) {
		if (data[i] > max) {
			max = data[i];
		}
	}
	return max;
}


/*
 * Finds the sum of the entries in data
 * 
 * data[]: array containing long integers
 * size: length of data array
 */
static long find_sum(long data[], long size) {
	long sum = 0;
	for (int i = 0; i < size; i++) {
		sum += data[i];
	}
	return sum;
}


/*
 * Handles testing the array_stats syscall
 * in situations where the syscall should always fail
 * 
 * stats: a pointer to an array_stats struct 
 * data[]: array containing long integers
 * size: length of data array
 * ret_code: the expected return code from the failed syscall
 */
static void do_syscall_failing(
  struct arrayStatsPtr stats, 
  long data[], 
  long size, 
  long ret_code
) {
  int result = do_syscall(stats, data, size);
	TEST(result == ret_code);
}


/*
 * Handles actually performing the syscall
 * 
 * stats: a pointer to an array_stats struct 
 * data: a pointer to an array containing long integers
 * size: length of data array
 */
static int do_syscall(
  struct arrayStatsPtr stats, 
  longPtr data, 
  long size
) {
	current_syscall_test_num++;

	printf("\nTest %d: ..Diving to kernel level\n", current_syscall_test_num);
	
  int result = syscall(_ARRAY_STATS_, stats, data, size);
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
 * Test for array_stats syscall
 */
void test_array_stats_syscall(void) {
  test_positive_few();

  test_negative_few();

  test_many();

  test_bad_addr();

  test_print_summary();
}