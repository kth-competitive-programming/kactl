/**
 * Author: Simon Lindholm
 * Date: 2015-09-12
 * Source: me
 * Description: When you need to dynamically allocate many objects and don't care about freeing them.
 * "new X" otherwise has an overhead of something like 0.05us + 16 bytes per allocation.
 * Usage: struct Node : Small { ... }; // (or inline it)
 * Status: tested
 */

static char buf[450<<20] alignas(16); // 450 MB
struct Small {
	void* operator new(size_t s) {
		static size_t i = 0;
		return (void*)&buf[i += s];
	}
};
