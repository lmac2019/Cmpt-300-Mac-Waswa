#ifndef BBUFF_H
#define BBUFF_H

#include "macros.h"
#include "pthread.h"
#include <stdlib.h>

typedef struct  {
    int factory_number;
    double time_stamp_in_ms;
} candy_t;

#define BUFFER_SIZE 10
#define candyStructPtr candy_t*

void bbuff_init(void);
void bbuff_blocking_insert(voidPtr item);
voidPtr bbuff_blocking_extract(void);
bool bbuff_is_empty(void);
bool bbuff_is_full(void);
void free_bbuff(void);

#endif