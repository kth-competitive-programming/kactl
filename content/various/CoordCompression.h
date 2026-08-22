/**
 * Author: Saadan Naqvi
 * Date: 2026-08-23
 * License: CC0
 * Source: folklore
 * Description: Replaces arbitrary values by their ranks, turning $n$ values
 * that may be huge or negative into the integers $0 \dots k-1$, where $k$ is
 * how many distinct values there are. Relative order is preserved, so the
 * ranks can index an array or a segment tree. Build it once from the values
 * you care about: \texttt{rank(x)} is then the rank of $x$, and
 * \texttt{sorted[i]} gives back the original value of rank $i$. A value that
 * was never seen gets the rank of the next larger value.
 * Usage: Compressor<int> comp(values);
 *  rep(i,0,sz(values)) values[i] = comp.rank(values[i]);
 * Time: O(n \log n) to build, O(\log n) per lookup
 * Status: Untested
 */
#pragma once

template<class T> struct Compressor {
	vector<T> sorted; // the distinct values, increasing
	Compressor(vector<T> values) : sorted(values) {
		sort(all(sorted));
		sorted.erase(unique(all(sorted)), sorted.end());
	}
	int rank(T value) {
		auto it = lower_bound(all(sorted), value);
		return int(it - sorted.begin());
	}
	int size() { return sz(sorted); }
};
