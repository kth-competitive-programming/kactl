#include "../utilities/template.h"

#include "../../content/various/FastMod.h"

// #define EIGHT

#ifdef EIGHT

// Compute k * (p-1)! % mod p. Should equal -k.
#define TEST() \
	INIT(0) \
	INIT(1) \
	INIT(2) \
	INIT(3) \
	INIT(4) \
	INIT(5) \
	INIT(6) \
	INIT(7) \
	for (int i = 1; i < mod; i++) { \
		UPDATE(0) \
		UPDATE(1) \
		UPDATE(2) \
		UPDATE(3) \
		UPDATE(4) \
		UPDATE(5) \
		UPDATE(6) \
		UPDATE(7) \
	} \
	FINISH(0) \
	FINISH(1) \
	FINISH(2) \
	FINISH(3) \
	FINISH(4) \
	FINISH(5) \
	FINISH(6) \
	FINISH(7)

#else

#define TEST() \
	INIT(0) \
	for (int i = 1; i < mod; i++) { \
		UPDATE(0) \
	} \
	FINISH(0)

#endif

void perf_plain(int mod) {
#define INIT(x) ll ret##x = (x + 1);
#define UPDATE(x) ret##x = (ret##x * i) % mod;
#define FINISH(x) cout << ret##x << endl;
	TEST()
#undef INIT
#undef UPDATE
#undef FINISH
}

template<int mod>
void perf_const() {
#define INIT(x) ll ret##x = (x + 1);
#define UPDATE(x) ret##x = (ret##x * i) % mod;
#define FINISH(x) cout << ret##x << endl;
	TEST()
#undef INIT
#undef UPDATE
#undef FINISH
}

void perf_barrett(int mod) {
	FastMod bar(mod);
#define INIT(x) ll ret##x = (x + 1);
#define UPDATE(x) ret##x = bar.reduce(ret##x * i);
#define FINISH(x) cout << ret##x << endl;
	TEST()
#undef INIT
#undef UPDATE
#undef FINISH
}

ull rand_u64() {
	ull ret = rand();
	ret <<= 23;
	ret ^= rand();
	ret <<= 23;
	ret ^= rand();
	return ret;
}

// Correctness
int main() {
	const int bflim = 3000;
	rep(a,0,bflim) rep(b,2,bflim) {
		FastMod bar(b);
		ull ret = bar.reduce(a);
		assert(ret == (ull)(a % b));
	}
	rep(it,0,10'000'000) {
		ull a = rand_u64();
		ull b = rand_u64();
		if (b <= 1) continue;
		FastMod bar(b);
		ull ret = bar.reduce(a);
		assert(ret == a % b);
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}

// Performance
int main2(int argc, char** argv) {
	const int which = atoi(argv[1]);
#ifndef MOD
#define MOD 90217093 //202171241
#endif
	int mod = MOD;
	if (which < 0) mod = which;
	if (which == 0) perf_plain(mod); // 7.529 for 8, 1.714 for 1
	if (which == 1) perf_const<MOD>(); // 0.971 for 8, 0.499 for 1
	if (which == 2) perf_barrett(mod); // 1.094 for 8, 0.564 for 1
	return 0;
}
