/**
 * Author: hhhhaura
 * Date: 2022/08/06
 * Description: 
 * 	Compressed form of all substrings of string S.
 * 	link -- the longest suffix of current substring with different endpos.
 * 	Follow link from last to obtain all terminal states.
 * Usage: 
 * 	Number of different substrings. 
 * 	Smallest cyclic shift (S + S). 
 * 	Number of occurrences. 
 * 	Shortest non-appearing string. 
 * 	LCS of multiple strings.
 * Time: $O(|S|)$
 * Status: Not tested
 */
struct SAM {
	struct state {
		int len, link;
		map<char, int> ch;
	};
	const int P = 100000;
	vector<state> st;
	int sz, last;
	void init_() {
		last = 0, sz = 1;
		st.assign(P * 2, {0, -1, {}});
	}
	void extend(char c) {
		int cur = sz ++;
		st[cur].len = st[last].len + 1;
		int p = last;
		while(p != -1 && !st[p].ch.count(c)) {
			st[p].ch[c] = cur;
			p = st[p].link;
		}
		if(p == -1) st[cur].link = 0;
		else {
			int q = st[p].ch[c];
			if(st[p].len + 1 == st[q].len) st[cur].link = q;
			else {
				int cl = sz ++;
				st[cl] = st[q];
				st[cl].len = st[p].len + 1;

				while(p != -1) {
					st[p].ch[c] = cl;
					p = st[p].link;
				}
				st[q].link = st[cur].link = cl;
			}
		}
		last = cur;
	}
};

