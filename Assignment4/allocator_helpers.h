#ifndef ALLOCATOR_HELPERS_H
#define ALLOCATOR_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

void print_allocator_message(charPtr message);
void print_allocator_error_message(charPtr message);
void assign_compacted_blocks(voidPtr* before, voidPtr* after, voidPtr* blocks, int num_compacted_blocks);

#endif