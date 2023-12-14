#ifndef ARGS_H_INCLUDED
#define ARGS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define min(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _b : _a; })


typedef struct args {
    int* const array; 
    const size_t N;
    const int lbound;
    const int rbound;

    size_t result;
} args_t;

args_t create_args(int* const array, const size_t N, const int lbound, const int rbound);
void split_for_args(args_t *args, const size_t pool_size, args_t *argses, void *_args);


#endif