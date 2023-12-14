#ifndef REGULAR_H_INCLUDED
#define REGULAR_H_INCLUDED
#include <stddef.h>
#include <stdbool.h>
#include "args_struct.h"

size_t i32_count_in_range(void* args);

static void* process(void* args); 

static void counter_func(const int lbound, int *p, const int rbound, size_t *result);

#endif