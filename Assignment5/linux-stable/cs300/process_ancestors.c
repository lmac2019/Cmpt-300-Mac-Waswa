#include <asm/current.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include "process_ancestors.h"

asmlinkage long sys_process_ancestors(
  struct process_info info_array[],
  long size,
  long *num_filled
){
  long i;
  struct task_struct *cur_task;
  struct list_head *head;
  struct process_info process;
  process.num_children = 0;
  process.num_siblings = 0;

  printk("size: %ld\n", size);

  if (size <= 0) {
    printk("error - invalid argument: size must be > 0\n");
    return -EINVAL;
  }

  cur_task = current;
  for (i = 0; cur_task != cur_task->parent; i++, cur_task = cur_task->parent) {
    
    process.pid = cur_task->pid;
    printk("process[%ld].pid: %ld\n", i, process.pid);    

    memcpy(process.name, cur_task->comm, TASK_COMM_LEN);
    printk("process[%ld].name: %s\n", i, process.name);   

    process.uid = (long)(cur_task->cred->uid.val);
    printk("process[%ld].uid: %ld\n", i, process.uid);   

    process.state = cur_task->state;
    printk("process[%ld].state: %ld\n", i, process.state);   

    process.nvcsw = cur_task->nvcsw;
    printk("process[%ld].nvcsw: %ld\n", i, process.nvcsw);   

    process.nivcsw = cur_task->nivcsw;
    printk("process[%ld].nivcsw: %ld\n", i, process.nivcsw);  

    list_for_each(head, &cur_task->children) {
      process.num_children += 1;
    }
    printk("process[%ld].num_children: %ld\n", i, process.num_children);  

    list_for_each(head, &cur_task->sibling) {
      process.num_siblings += 1;
    }
    printk("process[%ld].num_siblings: %ld\n", i, process.num_siblings);  

    if (__copy_to_user(&info_array[i], &process, sizeof(process))) {
      printk("error - bad address in info array\n");
      return -EFAULT;
    }
  }
  if (__copy_to_user(num_filled, &i, sizeof(i))) {
    printk("error - bad address in num_filled\n");
    return -EFAULT;
  }

  return 0;
}
