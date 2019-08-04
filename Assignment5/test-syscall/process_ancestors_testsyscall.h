// Structure to hold values returned by process_ancestors sys-call
#ifndef PROCESS_ANCESTORS_TESTSYSCALL_H
#define PROCESS_ANCESTORS_TESTSYSCALL_H

#include "test.h"

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

// * Working tests
void test_odd_size(void);
void test_even_size(void);

// * Failing tests
void test_zero_size(void);
void test_negative_odd_size(void);
void test_negative_even_size(void);
void test_process_ancestors_bad_address(void);

// * Helper functions
void do_process_ancestors_syscall_working(long size);
void do_process_ancestors_syscall_failing(struct processInfoPtr info_array, long size, longPtr num_filled, long ret_code);
int do_process_ancestors_syscall(struct process_info info_array[], long size, longPtr num);
void test_process_ancestors_print_summary(void);

// * Test function
void test_process_ancestors_syscall(void);

#endif