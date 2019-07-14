#include "fit_tests.h"

/*
 * Performs a fit test for integers that fill up the 
 * contiguous memory allocator
 * algorithm: type of allocation algorithm to be used
 */
void fit_fill_integers (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nfit_fill_integers\n");

  initialize_allocator(size, algorithm);

  intPtr integers[6] = { NULL };
  for (int i = 0; i < 6; ++i) {
    integers[i] = kalloc(sizeof(int));
    if (integers[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(integers[i]) = i;
    printf("integers[%d] = %p; *integers[%d] = %d\n", i, integers[i], i, *(integers[i]));
  }

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with the left most space
 * being bigger than the right most space
 * algorithm: type of allocation algorithm to be used
 */
void larger_left_most_space_smaller_right_most_space (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nlarger_left_most_space_smaller_right_most_space\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating larger left most free memory
  for (int i = 0; i < 10; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating smaller right most free memory
  int small_space_size = 6;
  for (int i = size - 1; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with the left most space
 * being smaller than the right most space
 * algorithm: type of allocation algorithm to be used
 */
void smaller_left_most_space_larger_right_most_space (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nsmaller_left_most_space_larger_right_most_space\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating smaller left most free memory
  for (int i = 0; i < 6; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating larger right most free memory
  int small_space_size = 10;
  for (int i = size - 1; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with equal spaces left most and right most
 * algorithm: type of allocation algorithm to be used
 */
void equal_spaces_left_most_right_most (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nequal_spaces_left_most_right_most\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating equal left most free memory
  for (int i = 0; i < 6; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating equal right most free memory
  int small_space_size = 6;
  for (int i = size - 1; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with the left most space
 * being bigger than the space to the right (not at the end)
 * algorithm: type of allocation algorithm to be used
 */
void larger_left_most_space_smaller_to_the_right (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nlarger_left_most_space_smaller_to_the_right\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating larger left most free memory
  for (int i = 0; i < 10; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating smaller right free memory (not at the end)
  int small_space_size = 6;
  for (int i = size - 2; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with the left most space
 * being smaller than the space to the right (not at the end)
 * algorithm: type of allocation algorithm to be used
 */
void smaller_left_most_space_larger_to_the_right (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nsmaller_left_most_space_larger_to_the_right\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating smaller left most free memory
  for (int i = 0; i < 6; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating larger right free memory (not at the end)
  int small_space_size = 10;
  for (int i = size - 3; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with equal spaces left most and to the right (not at the end)
 * algorithm: type of allocation algorithm to be used
 */
void equal_spaces_left_most_to_the_right (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nequal_spaces_left_most_to_the_right\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating equal left most free memory
  for (int i = 0; i < 6; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating equal right free memory (not at the end)
  int small_space_size = 9;
  for (int i = size - 4; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with the space on the left (not at the end)
 * being bigger than the right most space
 * algorithm: type of allocation algorithm to be used
 */
void larger_on_the_left_space_smaller_right_most_space (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nlarger_on_the_left_space_smaller_right_most_space\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating larger left free memory (not at the end)
  for (int i = 1; i < 12; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating smaller right most free memory
  int small_space_size = 6;
  for (int i = size - 1; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with the space on the left (not at the end)
 * being smaller than the space to the right most
 * algorithm: type of allocation algorithm to be used
 */
void smaller_on_the_left_space_larger_right_most_space (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nsmaller_on_the_left_space_larger_right_most_space\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating smaller left free memory (not at the end)
  for (int i = 2; i < 7; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating larger right most free memory
  int small_space_size = 11;
  for (int i = size - 1; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with equal spaces left (not at the end) and right most
 * algorithm: type of allocation algorithm to be used
 */
void equal_spaces_on_the_left_right_most (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nequal_spaces_on_the_left_right_most\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating equal left most free memory
  for (int i = 3; i < 7; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating equal right free memory (not at the end)
  int small_space_size = 4;
  for (int i = size - 1; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with the space on the left (not at the end)
 * being bigger than the right space (not at the end)
 * algorithm: type of allocation algorithm to be used
 */
void larger_on_left_space_smaller_to_the_right (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nlarger_on_left_space_smaller_to_the_right\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating larger left free memory (not at the end)
  for (int i = 1; i < 12; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating smaller right free memory (not at the end)
  int small_space_size = 6;
  for (int i = size - 2; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with the space on the left (not at the end)
 * being smaller than the space to the right (not at the end)
 * algorithm: type of allocation algorithm to be used
 */
void smaller_on_left_space_larger_to_the_right (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nsmaller_on_left_space_larger_to_the_right\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating smaller left free memory (not at the end)
  for (int i = 2; i < 7; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating larger right free memory (not at the end)
  int small_space_size = 11;
  for (int i = size - 3; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}

/*
 * Performs a test for integers and characters 
 * where initially memory is filled with characters
 * then two spaces are freed with equal spaces left (not at the end) and right (not at the end)
 * algorithm: type of allocation algorithm to be used
 */
void equal_spaces_on_the_left_to_the_right (enum allocation_algorithm algorithm) {
  int size = 24;
  print_allocator_message("\nequal_spaces_on_the_left_to_the_right\n");

  initialize_allocator(size, algorithm);

  charPtr characters[24] = { NULL };
  for (int i = 0; i < 24; ++i) {
    characters[i] = kalloc(sizeof(char));
    if (characters[i] == NULL) {
      print_allocator_message("Allocation failed");
      continue;
    }
    *(characters[i]) = 'a' + i;
    printf("characters[%d] = %p; *characters[%d] = %c\n", i, characters[i], i, *(characters[i]));
  }

  print_statistics();

  // * Creating equal left free memory (not at the end)
  for (int i = 3; i < 7; ++i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  // * Creating equal right free memory (not at the end)
  int small_space_size = 7;
  for (int i = size - 4; i >= size - small_space_size; --i) {
    printf("Freeing characters[%d]\n", i);
    kfree(characters[i]);
    characters[i] = NULL;
  }

  print_statistics();

  intPtr integer = NULL;
  integer = kalloc(sizeof(int));
  if (integer == NULL) {
    print_allocator_message("Allocation failed");
  }
  *integer = 1;
  printf("integer = %p; *integer = %d\n", integer, *integer);

  print_statistics();

  destroy_allocator();

  return;
}