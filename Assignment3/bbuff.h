#ifndef BBUFF_H
#define BBUFF_H

#include "macros.h"
#include "pthread.h"
#include <stdlib.h>
#include "helpers.h"

struct candyStruct {
  int factory_number;
  double time_stamp_in_ms;
};

#define BUFFER_SIZE 10
#define candyStructPtr candyStruct*

void bbuff_init(void);
void bbuff_blocking_insert(voidPtr item);
voidPtr bbuff_blocking_extract(void);
bool bbuff_is_empty(void);
bool bbuff_is_full(void);

#endif