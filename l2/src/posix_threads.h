#ifndef POSIX_THREADS_H_INCLUDED
#define POSIX_THREADS_H_INCLUDED

#include <stddef.h>

#ifdef __linux__ 
#include <pthread.h>
#elif _WIN32

#endif

#include "args_struct.h"

static void *process(void *_args);
static void counter_func(const int lbound, int *p, const int rbound, size_t *result);
size_t i32_count_in_range_pthread(void*, const size_t);


#ifdef __linux__
void pthread_create_all(const size_t pool_size, pthread_t *pool, args_t *argses);
void pthread_join_all(const size_t pool_size, pthread_t *pool, args_t *argses);
#elif _WIN32
#include <windows.h>
size_t i32_count_in_range_pthread(void*, const size_t);
void wthread_create_all(const size_t pool_size, HANDLE *pool, args_t *argses);
void wthread_join_all(const size_t pool_size, HANDLE *pool, args_t *argses);
#endif

#endif