#ifndef ARRAY_STATS_TESTSYSCALL_H
#define ARRAY_STATS_TESTSYSCALL_H

#include "globals.h"

struct array_stats{
  long min;
  long max;
  long sum;
};

#define arrayStatsPtr array_stats*

// * Working tests
void test_positive_few(void);
void test_negative_few(void);
void test_many(void);

// * Failing tests
void test_array_stats_bad_address(void);

// * Helper functions
void do_array_stats_syscall_working(long data[], long size);
void do_array_stats_syscall_failing(struct arrayStatsPtr stats, long data[], long size, long ret_code);
int do_array_stats_syscall(struct arrayStatsPtr stats, longPtr data, long size);
void test_array_stats_print_summary(void);

// * Internal testing framework
void array_stats_test_internal(bool success, int lineNum, charPtr argStr);

#define ARRAY_STATS_TEST(arg) array_stats_test_internal((arg), __LINE__, #arg)

// * Test function
void test_array_stats_syscall(void);

#endif