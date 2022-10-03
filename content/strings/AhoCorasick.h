/**
 * Author: hhhhaura
 * Date: 2022-10-03
 * Source: OI-wiki
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: Not tested
 */
#pragma once
struct AhoCorasick {
	enum { P = 26, st = 'a'};
	struct node { // zero-based
		array<int, P> ch = {0};
		int fail = 0, cnt = 0, dep = 0;
	};
	int cnt;
	vector<node> v;
	vector<int> ans;
	void init_(int mx) {
		v.clear();
		cnt = 1, v.resize(mx);
		v[0].fail = 0;
	}
	void insert(string s) {
		int p = 0, dep = 1;
		for(auto i : s) {
			int c = i - st;
			if(!v[p].ch[c]) {
				v[cnt].dep = dep;
				v[p].ch[c] = cnt ++;
			}
			p = v[p].ch[c], dep ++;
		}
		v[p].cnt ++;
	}
	void build(vector<string> s) {
		for(auto i : s) insert(i);
		queue<int> q;
		for(int i = 0; i < P; i ++) {
			if(v[0].ch[i]) q.push(v[0].ch[i]);
		}
		while(q.size()) {
			int p = q.front();
			q.pop();
			for(int i = 0; i < P; i ++) if(v[p].ch[i]) {
				int to = v[p].ch[i], cur = v[p].fail;
				while(cur && !v[cur].ch[i]) cur = v[cur].fail;
				if(v[cur].ch[i]) cur = v[cur].ch[i];
				v[to].fail = cur;
				v[to].cnt += v[cur].cnt;
				q.push(to);
			}
		}
	}
	void traverse(string s) {
		int p = 0;
		ans.assign(cnt, 0);
		for(auto i : s) {
			int c = i - st;
			while(p && !v[p].ch[c]) p = v[p].fail;
			if(v[p].ch[c]) {
				p = v[p].ch[c];
				ans[p] ++, v[p].cnt;
			}
		}
		vector<int> ord(cnt, 0);
		iota(all(ord), 0);
		sort(all(ord), [&](int a, int b) { return v[a].dep > v[b].dep; });
		for(auto i : ord) ans[v[i].fail] += ans[i];
		return;
	}
	int go(string s) {
		int p = 0;
		for(auto i : s) {
			int c = i - st;
			assert(v[p].ch[c]);
			p = v[p].ch[c];
		}
		return ans[p];
	}
};

