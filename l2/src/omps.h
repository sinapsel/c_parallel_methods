#ifndef OMPS_H_INCLUDED
#define OMPS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "args_struct.h"
#include <omp.h>

size_t i32_count_in_range_omp(void* _args, size_t div_size);
static void* process(void* _args);
static void counter_func(const int lbound, int *p, const int rbound, size_t *result);

#endif