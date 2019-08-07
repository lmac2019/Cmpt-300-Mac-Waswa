#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <linux/cred.h>
#include "process_ancestors.h"

asmlinkage long sys_process_ancestors(
  struct process_info info_array[],
  long size,
  long *num_filled
){
  struct process_info process;
  struct task_struct *cur_task;
  struct list_head *head;
  long num_children = 0;
  long num_siblings = 0;
  long i;
  long pid_value;
  char name_value[TASK_COMM_LEN];
  long uid_value;
  long state_value;
  long nvcsw_value;
  long nivcsw_value;

  printk("size: %ld\n", size);

  if (size <= 0) {
    printk("error - invalid argument: size must be > 0\n");
    return -EINVAL;
  }

  cur_task = current;
  for (i = 0; cur_task != cur_task->parent; i++, cur_task = cur_task->parent) {
    
    pid_value = cur_task->pid;
    printk("process[%ld].pid: %ld\n", i, pid_value);    
    process.pid = pid_value;

    strcpy(name_value, cur_task->comm);
    printk("process[%ld].name: %s\n", i, name_value);   
    strcpy(process.name, name_value);

    uid_value = (long)(cur_task->cred->uid.val);
    printk("process[%ld].uid: %ld\n", i, uid_value);   
    process.uid = uid_value;

    state_value = cur_task->state;
    printk("process[%ld].state: %ld\n", i, state_value);   
    process.state = state_value;

    nvcsw_value = cur_task->nvcsw;
    printk("process[%ld].nvcsw: %ld\n", i, nvcsw_value);   
    process.nvcsw = nvcsw_value;

    nivcsw_value = cur_task->nivcsw;
    printk("process[%ld].nivcsw: %ld\n", i, nivcsw_value);  
    process.nivcsw = nivcsw_value;

    list_for_each(head, &cur_task->children) {
      num_children++;
    }

    printk("process[%ld].num_children: %ld\n", i, num_children);  
    process.num_children = num_children;

    list_for_each(head, &cur_task->sibling) {
      num_siblings++;
    }

    printk("process[%ld].num_siblings: %ld\n", i, num_siblings);  
    process.num_siblings = num_siblings;

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
