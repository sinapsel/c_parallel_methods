#ifndef SMID_H_INCLUDED
#define SMID_H_INCLUDED
#include <immintrin.h>
#include <x86intrin.h>
#include <stddef.h>
// #include <stdbool.h>
static int hsum(__m256i);
int sum_and_exclude_intrinsic(int* array, size_t N, int treshold);
#endif