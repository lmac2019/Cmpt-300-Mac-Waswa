#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/list.h>
#include "process_ancestors.h"

asmlinkage long sys_process_ancestors(
  struct process_info info_array[],
  long size,
  long *num_filled
){
  struct process_info process;
  struct task_struct *cur_task;
  struct list_head *head;
  long children_num = 0;
  long sibling_num = 0;
  long i;

  if (size <= 0) {
    printk("error - invalid argument: size must be > 0\n");
    return -EINVAL;
  }

  cur_task = current;

  for (i = 0; cur_task != cur_task->parent; i++, cur_task = cur_task->parent) {
    process.pid = cur_task->pid;
    strcpy(process.name,cur_task->comm);
    process.uid = (long)(cur_task->cred->uid.val);
    process.state = cur_task->state;
    process.nvcsw = cur_task->nvcsw;
    process.nivcsw = cur_task->nivcsw;
    list_for_each(head, &cur_task->children) {
      children_num++;
    }

    process.num_children = children_num;
    list_for_each(head, &cur_task->sibling) {
      sibling_num++;
    }

    process.num_siblings = sibling_num;

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
