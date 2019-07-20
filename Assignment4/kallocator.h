#ifndef KALLOCATOR_H
#define KALLOCATOR_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"

enum allocation_algorithm { 
  FIRST_FIT, 
  BEST_FIT, 
  WORST_FIT
};

void print_allocator_message(charPtr message);
void print_allocator_error_message(charPtr message);
void assign_compacted_blocks(voidPtr *before, voidPtr *after, voidPtr *blocks, int num_compacted_blocks);

void initialize_allocator(int _size, enum allocation_algorithm _aalgorithm);
voidPtr kalloc(int _size);
void kfree(voidPtr _ptr);
int available_memory();
int allocated_memory();
void print_statistics();
int compact_allocation(voidPtr* _before, voidPtr* _after);
void destroy_allocator();

#endif