#pragma once
#if defined(__x86_64__) || defined(__i386__)
#include <x86intrin.h>

// (avoid using this) x86 only
ll rdtsc() { return __rdtsc(); }
#endif

ll tick() {
	struct timespec tp;
	if (clock_gettime(CLOCK_MONOTONIC, &tp)) abort();
	return tp.tv_sec * 1'000'000'000LL + tp.tv_nsec;
}

struct timeit {
	decltype(chrono::high_resolution_clock::now()) begin;
	const string label;
	timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
	~timeit() {
		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		cerr << duration << "ms elapsed [" << label << "]" << endl;
	}
};
