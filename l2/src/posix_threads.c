#include "posix_threads.h"
#include "bench.h"

static size_t _counter;

#ifdef __linux__
static pthread_mutex_t ptm_counter;
size_t i32_count_in_range_pthread(void* _args, const size_t pool_size) {

    // pthread_mutex_init(&ptm_counter, NULL);

    pthread_t* pool = (pthread_t*) malloc(sizeof(pthread_t) * (pool_size + 1));
    args_t* argses = (args_t*) malloc(sizeof(args_t) * (pool_size + 1));
    args_t* args = (args_t*) _args;
    args->result = 0;
    _counter = 0;


    split_for_args(args, pool_size, argses, _args);

    pthread_create_all(pool_size, pool, argses);
    pthread_join_all(pool_size, pool, argses);

    args->result = _counter;
    free(pool);
    free(argses);
    // pthread_mutex_destroy(&ptm_counter);

    return _counter;
}

void pthread_create_all(const size_t pool_size, pthread_t *pool, args_t *argses) {
    for (int i = 0; i <= pool_size; ++i) {
        pthread_create(pool + i, NULL, process, (void *)(argses + i));
    }
}

void pthread_join_all(const size_t pool_size, pthread_t *pool, args_t *argses) {
    for (int i = 0; i <= pool_size; ++i) {
        pthread_join(pool[i], NULL);
        _counter += argses[i].result;
    }
}

#elif _WIN32

size_t i32_count_in_range_pthread(void* _args, const size_t pool_size) {

    // pthread_mutex_init(&ptm_counter, NULL);

    HANDLE* pool = (HANDLE*) malloc(sizeof(HANDLE) * (pool_size + 1));
    args_t* argses = (args_t*) malloc(sizeof(args_t) * (pool_size + 1));
    args_t* args = (args_t*) _args;
    args->result = 0;
    _counter = 0;


    split_for_args(args, pool_size, argses, _args);

    wthread_create_all(pool_size, pool, argses);
    wthread_join_all(pool_size, pool, argses);

    args->result = _counter;
    free(pool);
    free(argses);
    // pthread_mutex_destroy(&ptm_counter);

    return _counter;
}


static DWORD WINAPI win_process(LPVOID _args) {
    args_t* args = (args_t*) _args;
    size_t* result = &(args->result);
    if (args->N < 0) {
        return 0;
    }
    for (int* p = args->array; p < args->array + args->N; p++) {
        counter_func(args->lbound, p, args->rbound, result);
    }

    ExitThread(0);
}
    
void wthread_create_all(const size_t pool_size, HANDLE *pool, args_t* argses) {
    for (int i = 0; i <= pool_size; ++i) {
        // HANDLE* t = malloc(sizeof(HANDLE*));

        *(pool + i) = CreateThread(NULL, 0, win_process, (LPVOID) &argses[i], 0, NULL);


        //pthread_create(pool + i, NULL, process, (void *)(argses + i));
    }
}

void wthread_join_all(const size_t pool_size, HANDLE *pool, args_t* argses) {
    WaitForMultipleObjects(pool_size, pool, TRUE, INFINITE);
    for (int i = 0; i <= pool_size; ++i) {
        CloseHandle(pool[i]);
        _counter += argses[i].result;
    }
}




#endif

static void* process(void* _args) {
    args_t* args = (args_t*) _args;
    size_t* result = &(args->result);
    if (args->N < 0) {
        return NULL;
    }
    for (int* p = args->array; p < args->array + args->N; p++) {
        counter_func(args->lbound, p, args->rbound, result);
    }

    // pthread_mutex_lock(&ptm_counter);
    // _counter += *result;
    // pthread_mutex_unlock(&ptm_counter);

    return NULL;
}

static void counter_func(const int lbound, int *p, const int rbound, size_t *result) {
    if ((lbound <= *p) && (*p < rbound)) {
        (*result)++;
    }
}