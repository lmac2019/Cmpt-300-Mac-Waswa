#include "kallocator.h"
#include "fit_tests.h"
#include "compact_allocation_tests.h"

int main (int argc, charPtr argv[]) {
  // * First Fit Tests
  fit_fill_integers(FIRST_FIT);

  larger_left_most_space_smaller_right_most_space(FIRST_FIT);
  smaller_left_most_space_larger_right_most_space(FIRST_FIT);
  equal_spaces_left_most_right_most(FIRST_FIT);

  larger_left_most_space_smaller_to_the_right(FIRST_FIT);
  smaller_left_most_space_larger_to_the_right(FIRST_FIT);
  equal_spaces_left_most_to_the_right(FIRST_FIT);


  // * Worst Fit Tests
  fit_fill_integers(WORST_FIT);

  larger_left_most_space_smaller_right_most_space(WORST_FIT);
  smaller_left_most_space_larger_right_most_space(WORST_FIT);
  equal_spaces_left_most_right_most(WORST_FIT);

  larger_left_most_space_smaller_to_the_right(WORST_FIT);
  smaller_left_most_space_larger_to_the_right(WORST_FIT);
  equal_spaces_left_most_to_the_right(WORST_FIT);

  larger_on_the_left_space_smaller_right_most_space(WORST_FIT);
  smaller_on_the_left_space_larger_right_most_space(WORST_FIT);
  equal_spaces_on_the_left_right_most(WORST_FIT);

  larger_on_left_space_smaller_to_the_right(WORST_FIT);
  smaller_on_left_space_larger_to_the_right(WORST_FIT);
  equal_spaces_on_the_left_to_the_right(WORST_FIT);


  // * Best Fit Tests
  fit_fill_integers(BEST_FIT);

  larger_left_most_space_smaller_right_most_space(BEST_FIT);
  smaller_left_most_space_larger_right_most_space(BEST_FIT);
  equal_spaces_left_most_right_most(BEST_FIT);

  larger_left_most_space_smaller_to_the_right(BEST_FIT);
  smaller_left_most_space_larger_to_the_right(BEST_FIT);
  equal_spaces_left_most_to_the_right(BEST_FIT);

  larger_on_the_left_space_smaller_right_most_space(BEST_FIT);
  smaller_on_the_left_space_larger_right_most_space(BEST_FIT);
  equal_spaces_on_the_left_right_most(BEST_FIT);

  larger_on_left_space_smaller_to_the_right(BEST_FIT);
  smaller_on_left_space_larger_to_the_right(BEST_FIT);
  equal_spaces_on_the_left_to_the_right(BEST_FIT);


  // * Compact Allocation Tests
  compact_allocation_scattered_characters();

  return 0;
}