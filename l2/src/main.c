#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "bench.h"
#include "regular.h"
#include "regular_sep.h"
#include "posix_threads.h"
#include "omps.h"

const size_t RMAX = 32;
int* const generate_sequence(int* const, const size_t);
void print_sequence(int* const, const size_t);


// const char CONST_PROC_FLAG[] = "-c";
// const char CONST_SIZE_FLAG[] = "-s";
// const char CONTC_TEST_FLAG[] = "-t";

int main(int argc, char* argv[]) {
    srand(time(NULL));


    uint64_t NUM;
    size_t N;
    int a, b;

    scanf("%lu %lu %d %d", &NUM, &N, &a, &b);
    int* const _arr = (int* const) malloc(N * sizeof(int));
    generate_sequence(_arr, N);
    // print_sequence(_arr, N);
    // printf("NUM N DEFAULT THREAD OMP\n");

    args_t args = {_arr, N, a, b, 0};
    // size_t res;

    printf("%lu, %lu, ", NUM, N);


    printf("%lu, ", tick_benchmark(i32_count_in_range_sep, (void*) &args, NUM));
    // printf("\t%lu\n", args.result);


    printf("%lu, ", tick_benchmark(i32_count_in_range_pthread, (void*)&args, NUM));
    // printf("\t%lu\n", args.result);


    printf("%lu;\n", tick_benchmark(i32_count_in_range_omp, (void*)&args, NUM));
    // printf("\t%lu\n", args.result);

    
    free(_arr);
    return 0;
}



void print_sequence(int* const array, const size_t N) {
    for (size_t i = 0; i<N; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int* const generate_sequence(int* const array, const size_t N){
    for (size_t i = 0; i<N; ++i) {
        array[i] = rand() % RMAX;
    }
    return array;
}