#ifndef TEST_H
#define TEST_H

#include "globals.h"

#define bool _Bool
#define arrayStatsPtr array_stats*
#define longPtr long*
#define charPtr char*
#define processInfoPtr process_info*

void test_internal(bool success, int lineNum, charPtr argStr);
void reset();

/*
 * Macro to allow us to get the line number, and argument's text:
 */ 
#define TEST(arg) test_internal((arg), __LINE__, #arg)

#endif