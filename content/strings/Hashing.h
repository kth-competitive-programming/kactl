/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Various self-explanatory methods for string hashing.
 * Status: tested
 */
#pragma once

typedef unsigned long long H;
static const H C = 123891739; // arbitrary

// Arithmetic mod 2^64-1. 5x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse).
// "typedef H K;" instead if you think test data is random.
struct K {
	typedef __uint128_t H2;
	H x; K(H x=0) : x(x) {}
	K operator+(K o){ return x + o.x + H(((H2)x + o.x)>>64); }
	K operator*(K o){ return K(x*o.x)+ H(((H2)x * o.x)>>64); }
	H operator-(K o) { K a = *this + ~o.x; return a.x + !~a.x; }
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
