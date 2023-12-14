#include "omps.h"

static size_t _counter = 0;

size_t i32_count_in_range_omp(void* _args, size_t div_size) {
    args_t* argses = (args_t*) malloc(sizeof(args_t) * (div_size + 1));
    args_t* args = (args_t*) _args;
    args->result = 0;

    size_t count = 0;

    split_for_args(args, div_size, argses, _args);

    #pragma omp parallel for reduction(+:count)
    for (int i = 0; i <= div_size; ++i) {
        process(&argses[i]);
        count += argses[i].result;
    }

    args->result = count;

    free(argses);
    return count;
}

static void* process(void* _args) {
    args_t* args = (args_t*) _args;
    size_t* result = &(args->result);

    for (int* p = args->array; p < args->array + args->N; p++) {
        counter_func(args->lbound, p, args->rbound, result);
    }

    return NULL;
}

static void counter_func(const int lbound, int *p, const int rbound, size_t *result) {
    if ((lbound <= *p) && (*p < rbound)) {
        (*result)++;
    }
}
