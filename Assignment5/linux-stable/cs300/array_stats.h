// Define the array_stats struct for the array_stats sys-call.
#ifndef _ARRAY_STATS_H_
#define _ARRAY_STATS_H_

#include "limits.h"

struct array_stats {
  long min; 
  long max;
  long sum;
};

#define arrayStatsPtr array_stats*

asmlinkage long sys_array_stats(
  struct arrayStatsPtr stats,
  long data[],
  long size
);

#endif