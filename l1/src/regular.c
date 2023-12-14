#include "regular.h"

int sum_and_exclude(int* array, size_t N, int treshold){
    int sum = 0;
    int delta = 0;
    bool mask = false;
    int tmp = 0;

    int cond_delta = 0;
    for (size_t i = 0; i<N; i++) {
        tmp = array[i];
        delta = tmp - treshold;
        mask = delta > 0;
        cond_delta = delta * (int) (mask);
        sum += cond_delta;
        tmp -= cond_delta;
        array[i] = tmp;
    }
    return sum;
}