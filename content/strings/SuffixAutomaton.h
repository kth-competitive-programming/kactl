/**
 * Author: Sachin Sivakumar
 * Date: 2025-01-24
 * Description: Creates a partial DFA (DAG) that accepts all suffixes, with suffix links.
 * One-to-one map between a path from the root and a substring.
 * len is the longest-length substring ending here.
 * pos is the first index in the string matching here.
 * term is whether this node is a terminal (aka a suffix)
 * Time: construction takes $O(N\log K)$, where $K =$ Alphabet Size.
 * Status: works but not stress tested
 */
#pragma once

struct st {int len, pos, term, link=-1; map<char, int> next;};
struct SuffixAutomaton {
	vector<st> a;
	SuffixAutomaton(string &str) {
		a.resize(1);
		int last = 0;
		for(auto c : str) {
			int p = last, cur = last = sz(a);
			a.push_back({a[p].len + 1, a[p].len});
			while(p >= 0 && !a[p].next.count(c))
				a[p].next[c] = cur, p = a[p].link;
			if (p == -1) a[cur].link = 0;
			else {
				int q = a[p].next[c];
				if (a[p].len + 1 == a[q].len) a[cur].link = q;
				else {
					a.push_back(a[q]);
					a.back().len = a[p].len + 1;
					for(; p >= 0 && a[p].next[c] == q; p = a[p].link)
						a[p].next[c] = sz(a)-1;
					a[q].link = a[cur].link = sz(a)-1;
				}
			}
		}
		while(last >= 0) a[last].term = 1, last = a[last].link;
	}
};
