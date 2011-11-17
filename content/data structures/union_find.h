/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * Source: folklore
 * Description: In the beginning every set contains one element. The only
 * allowed operation is set union. You can make a query whether two elements are
 * in the same set.
 * Time: $O(\log^* N)$, that is less than 6 for any reasonable $N$.
 */
#pragma once
#include <vector>
using namespace std;

struct union_find {
	vector<int> e;

	union_find(int n) {
		e.assign(n, -1);
	}

	bool same_set(int a, int b){ return (find(a)==find(b));}

	void join(int a, int b) { // union sets
		a = find(a); b = find(b);
		if (a == b) return;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
	}

	int find(int x) { // Find set-head with path-compression
		if (e[x] < 0) return x;
		return e[x] = find(e[x]);
	}

};
