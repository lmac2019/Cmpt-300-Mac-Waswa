#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include "process_ancestors.h"


asmlinkage long sys_process_ancestors(
  struct process_info info_array[],
  long size,
  long *num_filled
){

  struct process_info process;
  struct task_struct *task;
  struct list_head *list;

  if (size <= 0) {
    printk("error - invalid argument: size must be <= 0\n");
    return -EINVAL;
  }

  printk("size: %ld\n",size);

  return 0;

 }
