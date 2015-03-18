/**
 * Author: Simon Lindholm
 * Date: 2015-03-18
 * Source: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 * Description: Cheat sheet of SSE/AVX intrinsics, for doing arithmetic on several numbers at once. Can provide a constant factor improvement of about 4.
 * Operations follow the pattern \texttt{"\_mm(256)?\_name\_(si(128|256)|epi(8|16|32|64)|pd|ps)"}. Not all are described here;
 * grep for \texttt{\_mm\_} in \texttt{/usr/lib/gcc/{*}/4.9/include/} for more.
 * If AVX is unsupported, try 128-bit operations, "emmintrin.h" and \#define \texttt{\_\_SSE\_\_} and \texttt{\_\_MMX\_\_} before including it.
 * Memory must be aligned, so use \texttt{\_mm\_malloc(size, 32)} or \texttt{\_\_attribute\_\_((aligned(32)))} for 256 bits.
 */
#pragma once

#pragma GCC target ("avx,avx2,arch=corei7") // mmx,sse, etc.
#include "immintrin.h" /** keep-include */

typedef __m256i mi;
#define M32(x) _mm256_##x##_epi32

// High-level/specific methods:
// load(u)?_si256, store(u)?_si256, setzero_si256, _mm_malloc
// blendv_(epi8|ps|pd) (z?x:y), movemask_epi8 (hibits of bytes)
// i32gather(addr, x, 4): map addr[] over each 32-bit part of x
// sad_epu8: sum of absolute differences of u8, outputs 4xi64
// extractf128_si256(, i) (256->128), cvtsi128_si32 (128->lo32)
// 128-bit: shuffle: _mm_shuffle_epi32(x, 3*64+2*16+1*4+0) == x

// Methods that work with most data types (append e.g. _epi32):
// extract, set1, hadd, blend (i8?x:y), add, adds (sat.), mullo
// sub, and/or, andnot, abs, min, max, sign(1,x), cmp(lt|gt|eq)

int geti32(mi m, int i) {
	union {int v[8]; mi m;} u; u.m = m; return u.v[i]; }
mi undef() { return _mm256_undefined_si256(); }
mi zero() { return _mm256_setzero_si256(); }
mi one() { return _mm256_cmpeq_epi8(undef(), undef()); }
bool all_zero(mi m) { return _mm256_testz_si256(m, m); }
bool all_one(mi m) { return _mm256_testc_si256(zero(), m); }

// Example application (runs 3x faster than w/ unrolled loops):
vector<int*> floydWarshall(int N, int E) {
	N = ((N-1)|7)+1;
	vector<int*> d(N); int a, b, di;
	rep(i,0,N) d[i] = (int*)_mm_malloc(N*4, 256/8);
	rep(i,0,N) rep(j,0,N) d[i][j] = (i == j ? 0 : 1 << 29);
	rep(i,0,E) scanf("%d%d%d", &a, &b, &di), d[a][b] = di;
	rep(k,0,N) rep(i,0,N) {
		mi dik = M32(set1)(d[i][k]);
		mi *di = (mi*)d[i], *dk = (mi*)d[k];
		rep(j,0,N/8) di[j] = M32(min)(di[j], M32(add)(dik, dk[j]));
	}
	return d;
}
