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
 * 	LCS (substring)  of multiple strings.
 * Time: $O(|S|)$
 * Status: Not tested
 */
struct SAM {
	const int P = 100000;
	vector<map<char, int>> ch;
	vector<int> len, link;
	int sz, last;
	void init_() { 
		sz = 1, last = 0;
		ch.assign(P * 2, map<char, int>());
		len.assign(P * 2, 0);
		link.assign(P * 2, -1);
	}
	void extend(char c) {
		int cur = sz ++;
		len[cur] = len[last] + 1;
		int p = last;
		while(p != -1 && !ch[p].count(c)) {
			ch[p][c] = cur;
			p = link[p];
		}
		if(p == -1) link[cur] = 0;
		else {
			int q = ch[p][c];
			if(len[p] + 1 == len[q]) link[cur] = q;
			else {
				int cl = sz ++;
				ch[cl] = ch[q];
				len[cl] = len[p] + 1;
				link[cl] = link[q];
				while(p != -1 && ch[p].count(c) && ch[p][c] == q) {
					ch[p][c] = cl, p = link[p];
				}
				link[q] = link[cur] = cl;
			}
		}
		last = cur;
	}
};

