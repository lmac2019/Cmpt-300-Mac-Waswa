#include "kallocator.h"
#include <string.h>

int main (int argc, charPtr argv[]) {
  if(!strcmp(argv[1], "f")){
    initialize_allocator(100, FIRST_FIT);
    print_allocator_message("Using first fit algorithm on memory size 100");
  }

  if(!strcmp(argv[1], "b")){
    initialize_allocator(100, BEST_FIT);
    printf("Using best fit algorithm on memory size 100\n");
  }

  if(!strcmp(argv[1], "w")){
    initialize_allocator(100, WORST_FIT);
    printf("Using worst fit algorithm on memory size 100\n");
  }
  intPtr p[50] = { NULL };
  for (int i = 0; i < 10; ++i) {
    p[i] = kalloc(i+4);
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
  print_statistics();

  // p[1] = kalloc(sizeof(int));
  // if (p[1] == NULL) {
  //   print_allocator_message("Allocation failed");
  // }
  // *(p[1]) = 444;
  // printf("p[%d] = %p; *p[%d] = %d\n", 1, p[1], 1, *(p[1]));
  // print_statistics();
  // printf("available_memory %d", available_memory());

  print_statistics();

  printf("compact_allocation!\n");
    voidPtr before[100] = { NULL };
    voidPtr after[100] = { NULL };
    int num_compacted_blocks = compact_allocation(before, after);

    for (int i = 0; i < num_compacted_blocks; i++) {
      int j = -1;
      do {
        j++;
      } while (before[i] != p[j]);

      p[j] = after[i];
    }

    print_statistics();

    for (int i = 0; i < 10; i += 2) {
      printf("p[%d] = %p; *p[%d] = %d\n", i, p[i], i, *(p[i]));
    }

  destroy_allocator();

  return 0;
}
