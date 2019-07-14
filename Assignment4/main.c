#include "kallocator.h"
#include "fit_tests.h"
#include "compact_allocation_tests.h"

int main (int argc, charPtr argv[]) {
  // initialize_allocator(100, FIRST_FIT);
  // print_allocator_message("Using first fit algorithm on memory size 100");

  // // initialize_allocator(100, BEST_FIT);
  // // printf("Using best fit algorithm on memory size 100\n");
  
  // // initialize_allocator(100, WORST_FIT);
  // // printf("Using worst fit algorithm on memory size 100\n");

  // intPtr p[50] = { NULL };
  // for (int i = 0; i < 10; ++i) {
  //   p[i] = kalloc(sizeof(int));
  //   if (p[i] == NULL) {
  //     print_allocator_message("Allocation failed");
  //     continue;
  //   }
  //   *(p[i]) = i;
  //   printf("p[%d] = %p; *p[%d] = %d\n", i, p[i], i, *(p[i]));
  // }

  // print_statistics();

  // for (int i = 0; i < 10; ++i) {
  //   if (i % 2 == 0) {
  //     continue;
  //   }

  //   printf("Freeing p[%d]\n", i);
  //   kfree(p[i]);
  //   p[i] = NULL;
  // }

  // printf("available_memory %d\n", available_memory());

  // voidPtr before[100] = { NULL };
  // voidPtr after[100] = { NULL };
  // int num_compacted_blocks = compact_allocation(before, after);

  // for (int i = 0; i < num_compacted_blocks; i++) {
  //   int j = -1;
  //   do {
  //     j++;
  //   } while (before[i] != p[j]);
    
  //   p[j] = after[i];
  // }

  // print_statistics();

  // for (int i = 0; i < 10; i += 2) {
  //   printf("p[%d] = %p; *p[%d] = %d\n", i, p[i], i, *(p[i]));
  // }


  // destroy_allocator();

  // * First Fit Tests
  // fit_fill_integers(FIRST_FIT);

  // larger_left_most_space_smaller_right_most_space(FIRST_FIT);
  // smaller_left_most_space_larger_right_most_space(FIRST_FIT);
  // equal_spaces_left_most_right_most(FIRST_FIT);

  // larger_left_most_space_smaller_to_the_right(FIRST_FIT);
  // smaller_left_most_space_larger_to_the_right(FIRST_FIT);
  // equal_spaces_left_most_to_the_right(FIRST_FIT);

  // larger_on_the_left_space_smaller_right_most_space(FIRST_FIT);
  // smaller_on_the_left_space_larger_right_most_space(FIRST_FIT);
  // equal_spaces_on_the_left_right_most(FIRST_FIT);

  // larger_on_left_space_smaller_to_the_right(FIRST_FIT);
  // smaller_on_left_space_larger_to_the_right(FIRST_FIT);
  // equal_spaces_on_the_left_to_the_right(FIRST_FIT);

  // * Compact Allocation Tests
  compact_allocation_scattered_characters();

  return 0;
}