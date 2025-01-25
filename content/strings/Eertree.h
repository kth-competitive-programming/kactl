/**
 * Author: Jacob Steinebronn
 * Date: 2022-09-20
 * Description: Generates an eertree on str. $cur$ is accurate at the end of the main loop before the final assignment to $t$.
 * Time: $O(|S|)$
 * Status: Works but not stress-tested
 */

#pragma once

struct Eertree {
	vi slink = {0, 0}, len = {-1, 0};
	vvi down;
	int cur = 0, t = 0;
	Eertree(string &str) : down(2, vi(26, -1)) {
		for (int i = 0; i < sz(str); i++) {
			char c = str[i]; int ci = c - 'a';
			while (t <= 0 || str[t-1] != c) 
				t = i - len[cur = slink[cur]];
			if (down[cur][ci] == -1) {
				down[cur][ci] = sz(slink);
				down.emplace_back(26, -1);
				len.push_back(len[cur] + 2);
				if (len.back() > 1) {
					do t = i - len[cur = slink[cur]];
					while(t <= 0 || str[t-1] != c);
					slink.push_back(down[cur][ci]);
				} else slink.push_back(1);
				cur = sz(slink) - 1;
			} else cur = down[cur][ci];
			t = i - len[cur] + 1;
		}
	}
};
