#pragma once
#include <x86intrin.h>

// (avoid using this)
ll rdtsc() { return __rdtsc(); }

ll tick() {
	struct timespec tp;
	if (clock_gettime(CLOCK_MONOTONIC, &tp)) abort();
	return tp.tv_sec * 1'000'000'000LL + tp.tv_nsec;
}
