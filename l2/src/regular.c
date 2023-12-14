#include "regular.h"

size_t i32_count_in_range(void* _args) {
    process(_args);
    return ((args_t*)_args)->result;
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
