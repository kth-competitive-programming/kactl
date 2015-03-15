/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * Source: own work
 * Description: Various self-explanatory methods for string hashing. If it helps, $333411^{-1} = 113144412244155211$ mod $2^{64}$.
 * Status: tested
 */

typedef unsigned long long H;
static const H C = 123891739; // arbitrary but always odd
struct HashInterval {
	vector<H> ha, pw;
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
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw *= C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		h = h * C + str[i] - pw * str[i-length];
		ret.push_back(h);
	}
	return ret;
}

H hashString(string& s) {
	H h = 0;
	trav(c, s) h = h*C + c;
	return h;
}
