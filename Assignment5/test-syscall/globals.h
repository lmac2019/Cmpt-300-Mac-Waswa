#ifndef ARRAY_STATS_TESTSYSCALL_CONSTANTS_H
#define ARRAY_STATS_TESTSYSCALL_CONSTANTS_H

/*
 * array stats syscall number
 */
#define _ARRAY_STATS_ 341


/*
 * process ancestors syscall number
 */
#define _PROCESS_ANCESTORS_ 342


/*
 * Maximum length of the name of a process
 */
#define ANCESTOR_NAME_LEN 16


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