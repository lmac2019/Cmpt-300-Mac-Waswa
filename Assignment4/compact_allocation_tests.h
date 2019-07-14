#ifndef COMPACT_ALLOCATION_H
#define COMPACT_ALLOCATION_H

#include "kallocator.h"

void compact_allocation_unscattered_characters(enum allocation_algorithm algorithm);
void compact_allocation_scattered_characters(enum allocation_algorithm algorithm);

#endif