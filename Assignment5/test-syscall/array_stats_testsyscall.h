#ifndef ARRAY_STATS_TESTSYSCALL_H
#define ARRAY_STATS_TESTSYSCALL_H

#define bool _Bool
#define arrayStatsPtr array_stats*
#define longPtr long*
#define charPtr char*

struct array_stats{
  long min;
  long max;
  long sum;
};

void test_positive_few(void);
void test_negative_few(void);
void test_many(void);
void fill(long data[], long size);
void test_bad_addr(void);
static void do_syscall_working(long data[], long size);
static long find_min(long data[], long size);
static long find_max(long data[], long size);
static long find_sum(long data[], long size);
static void do_syscall_failing(struct arrayStatsPtr stats, long data[], long size, long ret_code);
static int do_syscall(struct arrayStatsPtr stats, longPtr data, long size);
static void test_internal(bool success, int lineNum, charPtr argStr);
static void test_print_summary(void);
void test_array_stats_syscall(void);

#endif