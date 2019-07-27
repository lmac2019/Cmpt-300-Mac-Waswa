#include "array_stats.h"

asmlinkage long sys_array_stats (
  struct arrayStatsPtr stats,
  long data[],
  long size
) {
  long min = LONG_MAX;
  long max = LONG_MIN;
  long data_copy;
  long sum = 0; 
  struct array_stats values;

  if (size <= 0) {
    return -EINVAL;
  }

  for (int i = 0; i < size; i++) {
    if (copy_from_user(&data_copy, data[i], sizeof(data[i]))) {
      return -EFAULT;
    } 

    if (data_copy < min) {
      min = data_copy;
    }

    if (data_copy > max) {
      max = data_copy;
    }

    sum += data_copy;
  }
  
  values.min = min;
  values.max = max;
  values.sum = sum;

  if (copy_to_user(stats, &values, sizeof(values))) {
    return -EFAULT;
  }

  return 0;
}