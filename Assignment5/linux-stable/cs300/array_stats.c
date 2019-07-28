#include "array_stats.h"

asmlinkage long sys_array_stats (
  struct arrayStatsPtr stats,
  long data[],
  long size
) {
  long data_copy;
  
  struct array_stats values;
  values.min = LONG_MAX;
  values.max = LONG_MIN;
  values.sum = 0;

  printk("size: %d\n", size);

  if (size <= 0) {
    printk("error - invalid argument: size <= 0\n");
    return -EINVAL;
  }

  for (int i = 0; i < size; i++) {
    if (_copy_from_user(&data_copy, data[i], sizeof(data[i]))) {
      printk("error - bad address in data array\n");
      return -EFAULT;
    } 

    printk("data[%d]: %ld\n", i, data_copy);

    if (data_copy < values.min) {
      values.min = data_copy;
    }

    if (data_copy > values.max) {
      values.max = data_copy;
    }

    values.sum += data_copy;
  }
  
  if (_copy_to_user(stats, &values, sizeof(values))) {
    printk("error - bad address in stats struct\n");
    return -EFAULT;
  }

  printk("stats min: %ld\n", stats->min);
  printk("stats max: %ld\n", stats->max);
  printk("stats sum: %ld\n", stats->sum);

  return 0;
}