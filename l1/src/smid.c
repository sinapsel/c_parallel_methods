#include "smid.h"

static int hsum(__m256i x) {
    __m128i l = _mm256_extracti128_si256(x, 0);
    __m128i h = _mm256_extracti128_si256(x, 1);
    l = _mm_add_epi32(l, h);
    l = _mm_hadd_epi32(l, l);
    return _mm_extract_epi32(l, 0) + _mm_extract_epi32(l, 1);
}


int sum_and_exclude_intrinsic(int* const array, const size_t N, const int treshold){
    __m256i _delta, _cond_delta, _sum, _treshold, _zero, _mask, _block;

    _treshold = _mm256_set1_epi32(treshold);
    _zero = _mm256_set1_epi32(0);
    _sum = _mm256_setzero_si256();
    
    for (const int* p = array; p < array + N; p+=8) {
        _block = _mm256_load_si256((__m256i*)p); // read tmp = array[i-1]
        _delta = _mm256_sub_epi32(_block, _treshold); // int delta = array[i-1] - treshold;
        _mask = _mm256_cmpgt_epi32(_delta, _zero); // bool (delta > 0)
        _cond_delta = _mm256_and_si256(_delta, _mask); // int cond_delta = delta * (int) (delta > 0);
        _sum = _mm256_add_epi32(_sum, _cond_delta); // sum += cond_delta;
        _block = _mm256_sub_epi32(_block, _cond_delta); // array[i-1] -= cond_delta;
        _mm256_store_si256((__m256i*)p, _block); // write array[i-1] = tmp
    }

    return hsum(_sum);
}