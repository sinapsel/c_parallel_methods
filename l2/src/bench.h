#ifndef BENCH_H_INCLUDED
#define BENCH_H_INCLUDED

#include <stdint.h>
#include <string.h>
#include <cpuid.h>
#include <immintrin.h>
#include <x86intrin.h>


#if defined(__i386__)
unsigned long long rdtsc(void);size_t i32_count_in_range_sep(void* _args, size_t div_size) 

#elif defined(__x86_64__)   
unsigned long long rdtsc(void);
#endif

typedef size_t (*func_t)(void*, size_t);

uint64_t tickbegin();
uint64_t tickend();

uint64_t tick_benchmark(func_t, void*, size_t);

#endif