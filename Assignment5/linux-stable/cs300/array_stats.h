// Define the array_stats struct for the array_stats sys-call.
#ifndef _ARRAY_STATS_H_
#define _ARRAY_STATS_H_

struct array_stats {
  long min; 
  long max;
  long sum;
};

#define arrayStatsPtr array_stats*
#define voidPtr void*

#endif