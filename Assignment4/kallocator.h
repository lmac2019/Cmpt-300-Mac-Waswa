#ifndef __KALLOCATOR_H__
#define __KALLOCATOR_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

enum allocation_algorithm { 
  FIRST_FIT, 
  BEST_FIT, 
  WORST_FIT
};

void initialize_allocator(int _size, enum allocation_algorithm _aalgorithm);
voidPtr kalloc(int _size);
void kfree(voidPtr _ptr);
int available_memory();
void print_statistics();
int compact_allocation(voidPtr* _before, voidPtr* _after);
void destroy_allocator();

#endif