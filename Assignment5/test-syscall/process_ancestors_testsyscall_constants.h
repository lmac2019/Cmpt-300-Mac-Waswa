#ifndef ARRAY_STATS_TESTSYSCALL_CONSTANTS_H
#define ARRAY_STATS_TESTSYSCALL_CONSTANTS_H

/*
 * array stats syscall number
 */
#define _PROCESS_ANCESTORS_ 342


/*
 * Macro to allow us to get the line number, and argument's text:
 */ 
#define TEST(arg) test_internal((arg), __LINE__, #arg)


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

#endif