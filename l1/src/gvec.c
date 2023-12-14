#include "gvec.h"

union v8 {
    v8si vec;
    int nums[8];
    __m256i mv;
};

static int hsum(__m256i x) {
    __m128i l = _mm256_extracti128_si256(x, 0);
    __m128i h = _mm256_extracti128_si256(x, 1);
    l = _mm_add_epi32(l, h);
    l = _mm_hadd_epi32(l, l);
    return _mm_extract_epi32(l, 0) + _mm_extract_epi32(l, 1);
}


int sum_and_exclude_vectors(int* const array, const size_t N, const int treshold){
    v8si _delta, _cond_delta, _mask;
    union v8 _block = {0};
    v8si _sum = {0};

    for(int* p = array; p < array + N; p+=8) {
        memcpy(_block.nums, p, 8*sizeof(int)); // read tmp = array[i-1]
        _delta = (_block.vec) - treshold; // int delta = array[i-1] - treshold;
        _mask = _delta > 0; // bool (delta > 0)
        _cond_delta = _delta * ((-1)*_mask); // int cond_delta = delta * (int) (delta > 0); !!! IN GCC VEC EXT TRUE CASTS TO 1
        _sum = _sum + _cond_delta; // sum += cond_delta;
        (_block.vec) -= _cond_delta; // array[i-1] -= cond_delta;
        memcpy(p, _block.nums, 8*sizeof(int)); // write array[i-1] = tmp
    }
    return hsum(*(__m256i*)&_sum);
}