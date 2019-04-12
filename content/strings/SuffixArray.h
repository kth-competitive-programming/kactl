/**
 * Author: chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: "China"
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which is $i$'th in the sorted
 * suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for neighbouring
 * strings in the suffix array: \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n)
 * Status: fuzz-tested
 */
#pragma once

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string &str, int lim = 256) {
		auto s = str.c_str(); // to get a trailing zero
		int n = sz(str) + 1, k = 0, a, b;
		vi x(n), y(n), ind(n), ws(max(n, lim)), rank(n);
		sa = lcp = ind;
		rep(i,0,n) ws[x[i] = s[i]]++;
		rep(i,1,lim) ws[i] += ws[i - 1];
		for (int i = n; i--;) sa[--ws[x[i]]] = i;
		for (int j = 1, p = 0; p < n; j *= 2, lim = p) {
			p = 0;
			rep(i,n-j,n) y[p++] = i;
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			rep(i,0,n) ind[i] = x[y[i]];
			rep(i,0,lim) ws[i] = 0;
			rep(i,0,n) ws[ind[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[ind[i]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i-1], b = sa[i], x[b] =
				y[a] == y[b] && y[a + j] == y[b + j] ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
			        s[i + k] == s[j + k]; k++) ;
	}
};
