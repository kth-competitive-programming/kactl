#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll mod = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}

typedef vector<ll> vl;
int mul(int a, int b) { return (ll)a * b % mod; }
int sub(int a, int b) { return b > a ? a - b + mod : a - b; }
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
void ntt(vi &a, vi &rt, vi &rev, int n) {
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k) {
                int z = mul(rt[j + k], a[i + j + k]);
                a[i + j + k] = sub(a[i + j], z);
                a[i + j] = add(a[i + j], z);
            }
}

vl conv(const vi &a, const vi &b) {
    if (a.empty() || b.empty())
        return {};
    vl res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vi inl(n), inr(n);
    vi out(n), rt(n, 1);
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    int curL = (mod - 1) >> 2;
    for (int k = 2; k < n; k *= 2) {
        int z[] = {1, modpow(root, curL)};
        curL >>= 1;
        rep(i, k, 2 * k) rt[i] = mul(rt[i / 2], z[i & 1]);
    }
    copy(all(a), begin(inl)), copy(all(b), begin(inr));
    ntt(inl, rt, rev, n), ntt(inr, rt, rev, n);
    int invN = modpow(n, mod - 2);
    rep(i, 0, n) out[i] = mul(mul(inl[i], inr[i]), invN);
    reverse(out.begin() + 1, out.begin() + n);
    ntt(out, rt, rev, n);
    rep(i, 0, sz(res)) res[i] = out[i];
    return res;
}


vl simpleConv(vi a, vi b) {
	int s = sz(a) + sz(b) - 1;
	if (a.empty() || b.empty()) return {};
	vl c(s);
	rep(i,0,sz(a)) rep(j,0,sz(b))
		c[i+j] = (c[i+j] + (ll)a[i] * b[j]) % mod;
	trav(x, c) if (x < 0) x += mod;
	return c;
}

int ra() {
	static unsigned X;
	X *= 123671231;
	X += 1238713;
	X ^= 1237618;
	return (X >> 1);
}

int main() {
	ll res = 0, res2 = 0;
	int ind = 0, ind2 = 0;
	vi a, b;
	rep(it,0,6000) {
		a.resize(ra() % 10);
		b.resize(ra() % 10);
		trav(x, a) x = (ra() % 100 - 50+mod)%mod;
		trav(x, b) x = (ra() % 100 - 50+mod)%mod;
		trav(x, simpleConv(a, b)) res += x * ind++ % mod;
		trav(x, conv(a, b)) res2 += x * ind2++ % mod;
	}
	cout << res << ' ' << res2 << endl;
}
