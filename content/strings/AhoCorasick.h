/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize the automaton with create(patterns); the automaton start node will be at index 1.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll(\_, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunk, with sentinel bits for symbol boundaries.
 * Time: create is $O(26N)$ where $N$ is the sum of length of patterns.
 * find is $O(M)$ where $M$ is the length of the word. findAll is $O(NM)$.
 * Status: fuzz-tested
 */
#pragma once

struct AhoCorasick {
	enum {alpha = 26, first = 'A'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha]{}, pat = -1, t = -1, nmatches = 0;
		void p(int y, vi& L) { t = (pat == -1 ? pat : L[t]) = y; }
	};
	vector<Node> N;
	vi backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 1;
		trav(c, s) {
			int& m = N[n].next[c - first];
			if (m) n = m;
			else { n = m = sz(N); N.emplace_back(); }
		}
		backp.push_back(0);
		N[n].p(j, backp);
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(2) {
		rep(i,0,alpha) N[0].next[i] = 1;
		N[1].back = 0;
		rep(i,0,sz(pat)) insert(pat[i], i);

		vi q(sz(N)); int qe = q[0] = 1;
		rep(qi,0,qe) {
			int n = q[qi], prev = N[n].back;
			rep(i,0,alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (!ed) ed = y;
				else {
					N[ed].back = y;
					N[ed].p(N[y].pat, backp);
					N[ed].nmatches += N[y].nmatches;
					q[qe++] = ed;
				}
			}
		}
	}
	vi find(string word) {
		int n = 1;
		vi res; // ll count = 0;
		trav(c, word) {
			n = N[n].next[c - first];
			res.push_back(N[n].pat);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi> findAll(vector<string>& pat, string word) {
		vi r = find(word);
		vector<vi> res(sz(word));
		rep(i,0,sz(word)) {
			int ind = r[i];
			while (ind != -1) {
				res[i - sz(pat[ind]) + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};
