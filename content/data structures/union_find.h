/**
 * Author: Lukas
 * Date: 2009-10-26
 * Source: folklore
 * Description: nodes have either information about their
 * parent or they store the size of the set multiplied by one
 */
#pragma once
#include <vector>

struct union_find {
	vector<int> e;

	union_find(int n) {
		e.assign(n, -1);
	}

	int find(int x) { // Find set-head with path-compression
		if (e[x] < 0) return x;
		return e[x] = find(e[x]);
	}

	bool equal(int a, int b){ return (find(a)==find(b));}

	void join(int a, int b) { // union sets
		a = find(a); b = find(b);
		if (x == y) return;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
	}
};
