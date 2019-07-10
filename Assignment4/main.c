#include "kallocator.h"

int main (int argc, charPtr argv[]) {
  initialize_allocator(100, FIRST_FIT);
  print_allocator_message("Using first fit algorithm on memory size 100");

  // initialize_allocator(100, BEST_FIT);
  // printf("Using best fit algorithm on memory size 100\n");
  
  // initialize_allocator(100, WORST_FIT);
  // printf("Using worst fit algorithm on memory size 100\n");

  intPtr p[50] = { NULL };
  for (int i = 0; i < 10; ++i) {
    p[i] = kalloc(sizeof(int));
    if (p[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(p[i]) = i;
    printf("p[%d] = %p; *p[%d] = %d\n", i, p[i], i, *(p[i]));
  }

  print_statistics();

  for (int i = 0; i < 10; ++i) {
    if (i % 2 == 0) {
      continue;
    }

    printf("Freeing p[%d]\n", i);
    kfree(p[i]);
    p[i] = NULL;
  }

  printf("available_memory %d", available_memory());

  voidPtr before[100] = { NULL };
  voidPtr after[100] = { NULL };
  compact_allocation(before, after);

  print_statistics();

  destroy_allocator();

  return 0;
}