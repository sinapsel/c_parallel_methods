#ifndef GVEC_H_INCLUDED
#define GVEC_H_INCLUDED
#include <immintrin.h>
#include <x86intrin.h>
#include <stddef.h>
#include <string.h>

typedef int v8si __attribute__ ((vector_size (32), aligned(32)));

static int hsum(__m256i);
int sum_and_exclude_vectors(int* const, const size_t, const int);

#endif