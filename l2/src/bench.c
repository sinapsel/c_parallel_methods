#include "bench.h"

#pragma GCC target("avx2")
#pragma intrinsic(__rtdsc)

#if defined(__i386__)

unsigned long long rdtsc(void) {
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

#elif defined(__x86_64__)

unsigned long long rdtsc(void) {
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#endif

uint64_t tickbegin() {
    int dummy[4];
    __cpuid(0, dummy[0], dummy[1], dummy[2], dummy[3]);// Prevent the compiler from optimizing away the whole Serialize function:
    volatile int DontSkip = dummy[0];
    return rdtsc();
}

uint64_t tickend() {
    int dummy[4];
    int eax, ebx, ecx, edx;
    uint64_t r = rdtsc();
    __cpuid(0, dummy[0], dummy[1], dummy[2], dummy[3]);// Prevent the compiler from optimizing away the whole Serialize function:
    volatile int DontSkip = dummy[0];
    return r;
}

uint64_t tick_benchmark(func_t bench_func, void* _args, size_t div_size) {
    uint64_t tb, te, ticks, tb1, te1 = 0UL, tb2, te2 = 0UL;
    
    tb = tickbegin();
    size_t N = 100UL;
    for (size_t i=0; i<N; ++i ){
        tb1 = tickbegin();
        // te1 += tickend() - tb1;
        volatile int s = bench_func(_args, div_size);
        tb2 = tickbegin();
        // te2 += tickend() - tb2;
    }
    te = tickend();
    ticks = ((te - tb) - (te1 + te2))/N;
    return ticks;
}
