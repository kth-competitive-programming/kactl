/**
 * Author: Stanford, Simon Lindholm
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Compute/update sums of intervals. Can be changed to other associative operations, with some effort.
 * Time: O(\log N).
 * Status: untested
 */
#pragma once

struct LazySegmentTree {
	typedef ll T; typedef vector<T> vt;
	int N;
	vt leaf, upd;
	LazySegmentTree(vt& li) : N(sz(li)), leaf(4*N), upd(4*N) {
		build(1,0,N-1,li);
	}
	void build(int cur, int a, int b, vt& li) {
		if (a == b)
			leaf[cur] = li[a];
		else {
			int mid = (a+b)/2;
			build(2 * cur, a, mid, li);
			build(2 * cur + 1, mid+1, b, li);
			leaf[cur] = leaf[2*cur] + leaf[2*cur+1];
		}
	}
	void update(int a, int b, T val) { // add val to [a,b)
		assert(0 <= a && a <= b && b <= N);
		update(1,0,N-1,a,b-1,val);
	}
	void update(int cur, int L, int R, int a, int b, T val) {
		if(a <= L && R <= b)
			upd[cur] += val;
		else {
			leaf[cur] += (min(b,R)-max(a,L)+1) * val;
			int mid = (L+R)/2;
			if (mid >= a && L <= b)
				update(2*cur, L, mid, a, b, val);
			if (R >= a && mid+1 <= b)
				update(2*cur+1, mid+1, R, a, b, val);
		}
	}
	T query(int a, int b) { // compute sum of values in [a,b)
		assert(0 <= a && a <= b && b <= N);
		return query(1,0,N-1,a,b-1);
	}
	T query(int cur, int L, int R, int a, int b) {
		if (upd[cur]) {
			leaf[cur] += (R-L+1) * upd[cur];
			if (cur < 2*N) {
				upd[2*cur] += upd[cur];
				upd[2*cur+1] += upd[cur];
			}
			upd[cur] = 0;
		}
		if (a <= L && R <= b)
			return leaf[cur];
		int mid = (L+R)/2;
		T ret = 0;
		if (mid >= a && L <= b)
			ret += query(2*cur, L, mid, a, b);
		if (R >= a && mid+1 <= b)
			ret += query(2*cur+1, mid+1, R, a, b);
		return ret;
	}
};
