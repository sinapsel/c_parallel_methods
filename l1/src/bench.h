#ifndef BENCH_H_INCLUDED
#define BENCH_H_INCLUDED

#include <stdint.h>
#include <string.h>
#include <cpuid.h>
#include <immintrin.h>
#include <x86intrin.h>


#if defined(__i386__)
unsigned long long rdtsc(void);
#elif defined(__x86_64__)   
unsigned long long rdtsc(void);
#endif

typedef int (*func_t)(int* const, const size_t, const int);

uint64_t tickbegin();
uint64_t tickend();

uint64_t tick_benchmark(func_t, int* const, const size_t, const int);

#endif