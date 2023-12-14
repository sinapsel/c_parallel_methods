#include "args_struct.h"

args_t create_args(int* const array, const size_t N, const int lbound, const int rbound){ 
    return (args_t){array, N, lbound, rbound, 0};
}

void split_for_args(args_t *args, const size_t dividing_size, args_t *argses, void *_args) {
    size_t _batch = args->N / dividing_size; // + (size_t) (((args_t*)_args)->N % 16);

    void *_helping_ptr;
    for (int i = 0; i <= dividing_size; ++i) {
        memcpy(argses + i, _args, sizeof(args_t));
        _helping_ptr = (size_t *)(&argses[i].array);
        *(int **)_helping_ptr = args->array + _batch * i;
        _helping_ptr = (size_t *)(&argses[i].N);
        *(size_t *)_helping_ptr = min(_batch, args->N - _batch * i);
    }
}
