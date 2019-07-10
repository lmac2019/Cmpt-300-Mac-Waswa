#ifndef KALLOCATOR_H
#define KALLOCATOR_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "allocator_helpers.h"
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
int allocated_memory();
void print_statistics();
int compact_allocation(voidPtr* _before, voidPtr* _after);
void destroy_allocator();

#endif