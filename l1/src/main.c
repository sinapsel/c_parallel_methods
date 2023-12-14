#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "bench.h"
#include "regular.h"
#include "smid.h"
#include "gvec.h"


const size_t RMAX = 32;
// const size_t RMAX = 32767;

int* const generate_sequence(int* const, const size_t);
void print_sequence(int* const, const size_t);
int content_test(size_t, int);
int time_test(size_t, int);

const char CONT_FLAG[] = "-c";
const char TIME_FLAG[] = "-t";
    
int main(int argc, char* argv[]) {
    srand(time(NULL));
    size_t seq_len;
    int treshold;

    scanf("%lu %d", &seq_len, &treshold);


    if (argc >= 2) {
        if (!strcmp(argv[1], CONT_FLAG)) {
            return content_test(seq_len, treshold);
        }
        if (!strcmp(argv[1], TIME_FLAG)) {
            return time_test(seq_len, treshold);
        }
    }




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

int content_test(size_t seq_len, int treshold) {
    printf("content test\n");

    size_t capacity_len = (seq_len/8 + (int)(seq_len%8>0))*8; // extend to aligned form

    int* const _arr = (int* const) malloc(capacity_len * sizeof(int));
    generate_sequence(_arr, seq_len);

    printf("LINEAR\n");
    int* const arr = (int* const) malloc(capacity_len * sizeof(int));
    memcpy(arr, _arr, capacity_len*sizeof(int));
    print_sequence(arr, seq_len);
    uint64_t tb = tickbegin();
    int s = sum_and_exclude(arr, capacity_len, treshold);
    uint64_t dt = tickend() - tb;
    printf("\nsum: %d\n", s);
    print_sequence(arr, seq_len);
    printf("time: %lu\n", dt);

    printf("\n\n-----------------------------\n\n");

    printf("SMID INTRINSIC\n");
    int* const arr1 = (int* const) malloc(capacity_len * sizeof(int));
    memcpy(arr1, _arr, capacity_len*sizeof(int));
    print_sequence(arr1, seq_len);
    tb = tickbegin();
    int s1 = sum_and_exclude_intrinsic(arr1, capacity_len, treshold);
    dt = tickend() - tb;
    printf("\nsum: %d\n", s1);
    print_sequence(arr1, seq_len);
    printf("time: %lu\n", dt);

    printf("\n\n-----------------------------\n\n");

    printf("GCC VECTOR\n");
    int* arr2 = (int*) malloc(capacity_len * sizeof(int));
    memcpy(arr2, _arr, capacity_len*sizeof(int));
    print_sequence(arr2, seq_len);
    tb = tickbegin();
    int s2 = sum_and_exclude_vectors(arr2, capacity_len, treshold);
    dt = tickend() - tb;
    printf("\nsum: %d\n", s2);
    print_sequence(arr2, seq_len);
    printf("time: %lu\n", dt);

    printf("\n\n-----------------------------\n\n");
    free(arr);
    free(arr1);
    free(arr2);
    free(_arr);

    return 0;
}


int time_test(size_t seq_len, int treshold) {
    // printf("content test\n");

    size_t capacity_len = (seq_len/8 + (int)(seq_len%8>0))*8; // extend to aligned form

    int* const _arr = (int* const) malloc(capacity_len * sizeof(int));
    generate_sequence(_arr, seq_len);

    for (int i = 0; i < 5; i++) {
        printf("%lu, ", seq_len);
        printf("%lu, ", tick_benchmark(sum_and_exclude, _arr, capacity_len, treshold));
        printf("%lu, ", tick_benchmark(sum_and_exclude_intrinsic, _arr, capacity_len, treshold));
        printf("%lu\n", tick_benchmark(sum_and_exclude_vectors, _arr, capacity_len, treshold));
    }
    
    free(_arr);
    return 0;
}