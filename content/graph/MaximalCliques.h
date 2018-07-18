/**
 * Author: Simon Lindholm
 * Date: 2018-07-18
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
 * Description: Runs a callback for all maximal cliques in a graph (given as
 * a symmetric bitset matrix; self-edges not allowed).
 * Possible optimization: on the top-most recursion level, ignore 'cands', and
 * go through nodes in order of increasing degree, where degrees go down as
 * nodes are removed.
 * Time: O(2^{n/3}), much faster for sparse graphs
 * Status: fuzz-tested
 */
#pragma once

typedef bitset<128> B;
template<class F>
void rec(vector<B>& eds, B R, B P, B X, F f) {
	if (!P.any()) { if (!X.any()) f(R); return; }
	auto q = (P | X)._Find_first();
	auto cands = P & ~eds[q];
	rep(i,0,sz(eds)) if (cands[i]) {
		R[i] = 1;
		rec(eds, R, P & eds[i], X & eds[i], f);
		R[i] = P[i] = 0; X[i] = 1;
	}
}
template<class F>
void cliques(vector<B>& eds, F f) { rec(eds, {}, ~B(), {}, f);}
