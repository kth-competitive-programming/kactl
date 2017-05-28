/**
 * Author: Simon Lindholm
 * Date: 2015-03-18
 * License: CC0
 * Source: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 * Description: Cheat sheet of SSE/AVX intrinsics, for doing arithmetic on several numbers at once.
 * Can provide a constant factor improvement of about 4, orthogonal to loop unrolling.
 * Operations follow the pattern \texttt{"\_mm(256)?\_name\_(si(128|256)|epi(8|16|32|64)|pd|ps)"}. Not all are described here;
 * grep for \texttt{\_mm\_} in \texttt{/usr/lib/gcc/{*}/4.9/include/} for more.
 * If AVX is unsupported, try 128-bit operations, "emmintrin.h" and \#define \texttt{\_\_SSE\_\_} and \texttt{\_\_MMX\_\_} before including it.
 * For aligned memory use \texttt{\_mm\_malloc(size, 32)} or \texttt{int buf[N] alignas(32)}, but prefer loadu/storeu.
 */
#pragma once

#pragma GCC target ("avx2") // or sse4.1
#include "immintrin.h" /** keep-include */

typedef __m256i mi;
#define L(x) _mm256_loadu_si256((mi*)&(x))

// High-level/specific methods:
// load(u)?_si256, store(u)?_si256, setzero_si256, _mm_malloc
// blendv_(epi8|ps|pd) (z?y:x), movemask_epi8 (hibits of bytes)
// i32gather_epi32(addr, x, 4): map addr[] over 32-b parts of x
// sad_epu8: sum of absolute differences of u8, outputs 4xi64
// maddubs_epi16: dot product of unsigned i7's, outputs 16xi15
// madd_epi16: dot product of signed i16's, outputs 8xi32
// extractf128_si256(, i) (256->128), cvtsi128_si32 (128->lo32)
// permute2f128_si256(x,x,1) swaps 128-bit lanes
// shuffle_epi32(x, 3*64+2*16+1*4+0) == x for each lane
// shuffle_epi8(x, y) takes a vector instead of an imm

// Methods that work with most data types (append e.g. _epi32):
// set1, blend (i8?x:y), add, adds (sat.), mullo, sub, and/or,
// andnot, abs, min, max, sign(1,x), cmp(gt|eq), unpack(lo|hi)

int sumi32(mi m) { union {int v[8]; mi m;} u; u.m = m;
	int ret = 0; rep(i,0,8) ret += u.v[i]; return ret; }
mi zero() { return _mm256_setzero_si256(); }
mi one() { return _mm256_set1_epi32(-1); }
bool all_zero(mi m) { return _mm256_testz_si256(m, m); }
bool all_one(mi m) { return _mm256_testc_si256(m, one()); }

ll example_filteredDotProduct(int n, short* a, short* b) {
	int i = 0; ll r = 0;
	mi zero = _mm256_setzero_si256(), acc = zero;
	while (i + 16 <= n) {
		mi va = L(a[i]), vb = L(b[i]); i += 16;
		va = _mm256_and_si256(_mm256_cmpgt_epi16(vb, va), va);
		mi vp = _mm256_madd_epi16(va, vb);
		acc = _mm256_add_epi64(_mm256_unpacklo_epi32(vp, zero),
			_mm256_add_epi64(acc, _mm256_unpackhi_epi32(vp, zero)));
	}
	union {ll v[4]; mi m;} u; u.m = acc; rep(i,0,4) r += u.v[i];
	for (;i<n;++i) if (a[i] < b[i]) r += a[i]*b[i]; // <- equiv
	return r;
}
