// Structure to hold values returned by process_ancestors sys-call
#ifndef PROCESS_ANCESTORS_TESTSYSCALL_H
#define PROCESS_ANCESTORS_TESTSYSCALL_H

#define ANCESTOR_NAME_LEN 16

struct process_info {
  long pid;                     /* Process ID */
  char name[ANCESTOR_NAME_LEN]; /* Program name of process */
  long state;                   /* Current process state */
  long uid;                     /* User ID of process owner */
  long nvcsw;                   /* # voluntary context switches */
  long nivcsw;                  /* # involuntary context switches */
  long num_children;            /* # children process has */
  long num_siblings;            /* # sibling process has */
};

#define bool _Bool
#define longPtr long*
#define charPtr char*
#define processInfoPtr process_info*

// * Working tests
void test_odd_size(void);
void test_even_size(void);

// * Failing tests
void test_zero_size(void);
void test_negative_odd_size(void);
void test_negative_even_size(void);

// * Helper functions
static void do_syscall_working(long size);
static int do_syscall(struct process_info info_array[], long size, longPtr num);
static void test_internal(bool success, int lineNum, charPtr argStr);
static void test_print_summary(void);

// * Test function
void test_process_ancestors_syscall(void);

#endif