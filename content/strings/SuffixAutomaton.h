/**
 * Author: Jacob Steinebronn
 * Date: 2023-03-21
 * Description: Creates a partial DFA (DAG) that accepts all suffixes, with suffix links.
 * One-to-one map between a path from the root and a substring.
 * len is the longest-length substring ending here.
 * pos is the first index in the string matching here.
 * term is whether this node is a terminal (aka a suffix)
 * Time: construction takes $O(N\log K)$, where $K =$ Alphabet Size.
 * Status: works but not stress tested
 */
#pragma once

struct st { int len, pos, term; st *link; map<char, st*> next; };
st *suffixAutomaton(string &str) {
	st *last = new st(), *root = last;
	for(auto c : str) {
		st *p = last, *cur = last = new st{last->len + 1, last->len};
		while(p && !p->next.count(c))
			p->next[c] = cur, p = p->link;
		if (!p) cur->link = root;
		else {
			st *q = p->next[c];
			if (p->len + 1 == q->len) cur->link = q;
			else {
				st *clone = new st{p->len+1, q->pos, 0, q->link, q->next};
				for (; p && p->next[c] == q; p = p->link)
					p->next[c] = clone;
				q->link = cur->link = clone;
			}
		}
	}
	while(last) last->term = 1, last = last->link;
	return root;
}
