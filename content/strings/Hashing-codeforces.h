/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Various self-explanatory methods for string hashing.
 * Use on Codeforces, which lacks 64-bit support and where solutions can be hacked.
 * Status: somewhat tested
 */
#pragma once

typedef long long H;
static const H M = INT_MAX;
static H C; // initialized below

// Arithmetic mod M. "typedef H K;" instead if you think
// test data is random. (Haha, good luck.)
struct K {
	H x; K(H x=0) : x(x) {}
	K operator+(K o) { H y = x + o.x; return y - (y >= M) * M; }
	K operator*(K o) { return x*o.x % M; }
	H operator-(K o) { H y = x - o.x; return y + (y < 0) * M; }
};

struct HashInterval {
	vector<K> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	K h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h - 0};
	rep(i,length,sz(str)) {
		ret.push_back(h * C + str[i] - pw * str[i-length]);
		h = ret.back();
	}
	return ret;
}

H hashString(string& s) {
	K h = 0;
	trav(c, s) h = h * C + c;
	return h - 0;
}

#include <sys/time.h>
int main() {
	timeval tp;
	gettimeofday(&tp, 0);
	C = tp.tv_usec;
	// ...
}
