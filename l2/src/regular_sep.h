#ifndef REGULAR_SEP_H_INCLUDED
#define REGULAR_SEP_H_INCLUDED
#include <stddef.h>
#include <stdbool.h>
#include "args_struct.h"

size_t i32_count_in_range_sep(void* args, size_t div_size);

static void* process(void* args); 

static void counter_func(const int lbound, int *p, const int rbound, size_t *result);

static void count_processes_all(const size_t div_size, args_t *argses);

#endif