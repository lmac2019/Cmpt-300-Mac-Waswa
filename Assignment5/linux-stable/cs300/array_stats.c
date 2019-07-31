#include <linux/kernel.h>
#include "array_stats.h"

#define arrayStatsPtr array_stats*
#define voidPtr void*

asmlinkage long sys_array_stats (
  struct arrayStatsPtr stats,
  long data[],
  long size
) {
  long data_copy;
  int i;
  struct array_stats values;

  printk("size: %ld\n", size);

  if (size <= 0) {
    printk("error - invalid argument: size <= 0\n");
    return -EINVAL;
  }

  for (i = 0; i < size; i++) {
    if (_copy_from_user(&data_copy, (voidPtr) data[i], sizeof(data[i]))) {
      printk("error - bad address in data array\n");
      return -EFAULT;
    } 

    printk("data[%d]: %ld\n", i, data_copy);

    if (i == 0) {
      values.min = data_copy;
      printk("initial values.min: %ld\n", values.min);

      values.max = data_copy;
      printk("initial values.max: %ld\n", values.max);
      
      values.sum = data_copy;
      printk("initial values.sum: %ld\n", values.sum);
      
      continue;
    }

    if (data_copy < values.min) {
      printk("data_copy < values.min: %ld < %ld\n", data_copy, values.min);
      values.min = data_copy;
    }

    if (data_copy > values.max) {
      printk("data_copy > values.max: %ld > %ld\n", data_copy, values.max);
      values.max = data_copy;
    }

    printk("values sum before adding %ld: %ld\n", data_copy, values.sum);
    
    values.sum += data_copy;
    
    printk("values sum after adding %ld: %ld\n", data_copy, values.sum);
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