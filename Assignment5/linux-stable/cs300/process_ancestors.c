#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include "process_ancestors.h"


asmlinkage long sys_process_ancestors(
  struct process_info info_array[],
  long size,
  long *num_filled
){

  struct process_info process;
  struct task_struct *cur_task;
  // struct list_head *list;
  int i = 0;

  if (size <= 0) {
    printk("error - invalid argument: size must be <= 0\n");
    return -EINVAL;
  }
  cur_task = current;
  while(cur_task != cur_task->parent){
    process.pid = cur_task->pid;
    printk("current pid: %ld\n",process.pid);
    strcpy(process.name,cur_task->comm);
    printk("current pid: %s\n",process.name);
    cur_task = cur_task->parent;
    i++;
  }

  printk("size: %ld\n",size);

  return 0;

 }
