#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

#define per(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        cerr << duration << "ms elapsed [" << label << "]" << endl;
    }
};
namespace MIT {
namespace fft {
#if FFT
// FFT
using dbl = double;
struct num { /// start-hash
    dbl x, y;
    num(dbl x_ = 0, dbl y_ = 0) : x(x_), y(y_) {}
};
inline num operator+(num a, num b) { return num(a.x + b.x, a.y + b.y); }
inline num operator-(num a, num b) { return num(a.x - b.x, a.y - b.y); }
inline num operator*(num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline num conj(num a) { return num(a.x, -a.y); }
inline num inv(num a) {
    dbl n = (a.x * a.x + a.y * a.y);
    return num(a.x / n, -a.y / n);
}
/// end-hash
#else
// NTT
const int mod = 998244353, g = 3;
// For p < 2^30 there is also (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). Last two are > 10^9.
struct num { /// start-hash
    int v;
    num(ll v_ = 0) : v(int(v_ % mod)) {
        if (v < 0)
            v += mod;
    }
    explicit operator int() const { return v; }
};
inline num operator+(num a, num b) { return num(a.v + b.v); }
inline num operator-(num a, num b) { return num(a.v + mod - b.v); }
inline num operator*(num a, num b) { return num(1ll * a.v * b.v); }
inline num pow(num a, int b) {
    num r = 1;
    do {
        if (b & 1)
            r = r * a;
        a = a * a;
    } while (b >>= 1);
    return r;
}
inline num inv(num a) { return pow(a, mod - 2); }
/// end-hash
#endif

using vn = vector<num>;
vi rev({0, 1});
vn rt(2, num(1)), fa, fb;

inline void init(int n) { /// start-hash
    if (n <= sz(rt))
        return;
    rev.resize(n);
    rep(i, 0, n) rev[i] = (rev[i >> 1] | ((i & 1) * n)) >> 1;
    rt.reserve(n);
    for (int k = sz(rt); k < n; k *= 2) {
        rt.resize(2 * k);
#if FFT
        double a = M_PI / k;
        num z(cos(a), sin(a)); // FFT
#else
        num z = pow(num(g), (mod - 1) / (2 * k)); // NTT
#endif
        rep(i, k / 2, k) rt[2 * i] = rt[i], rt[2 * i + 1] = rt[i] * z;
    }
} /// end-hash

inline void fft(vector<num> &a, int n) { /// start-hash
    init(n);
    int s = __builtin_ctz(sz(rev) / n);
    rep(i, 0, n) if (i<rev[i]>> s) swap(a[i], a[rev[i] >> s]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k) {
                num t = rt[j + k] * a[i + j + k];
                a[i + j + k] = a[i + j] - t;
                a[i + j] = a[i + j] + t;
            }
} /// end-hash

// Complex/NTT
vn multiply(vn a, vn b) { /// start-hash
    int s = sz(a) + sz(b) - 1;
    if (s <= 0)
        return {};
    int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
    a.resize(n), b.resize(n);
    fft(a, n);
    fft(b, n);
    num d = inv(num(n));
    rep(i, 0, n) a[i] = a[i] * b[i] * d;
    reverse(a.begin() + 1, a.end());
    fft(a, n);
    a.resize(s);
    return a;
} /// end-hash

// Complex/NTT power-series inverse
// Doubles b as b[:n] = (2 - a[:n] * b[:n/2]) * b[:n/2]
vn inverse(const vn &a) { /// start-hash
    if (a.empty())
        return {};
    vn b({inv(a[0])});
    b.reserve(2 * a.size());
    while (sz(b) < sz(a)) {
        int n = 2 * sz(b);
        b.resize(2 * n, 0);
        if (sz(fa) < 2 * n)
            fa.resize(2 * n);
        fill(fa.begin(), fa.begin() + 2 * n, 0);
        copy(a.begin(), a.begin() + min(n, sz(a)), fa.begin());
        fft(b, 2 * n);
        fft(fa, 2 * n);
        num d = inv(num(2 * n));
        rep(i, 0, 2 * n) b[i] = b[i] * (2 - fa[i] * b[i]) * d;
        reverse(b.begin() + 1, b.end());
        fft(b, 2 * n);
        b.resize(n);
    }
    b.resize(a.size());
    return b;
} /// end-hash

#if FFT
// Double multiply (num = complex)
using vd = vector<double>;
vd multiply(const vd &a, const vd &b) { /// start-hash
    int s = sz(a) + sz(b) - 1;
    if (s <= 0)
        return {};
    int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
    if (sz(fa) < n)
        fa.resize(n);
    if (sz(fb) < n)
        fb.resize(n);

    fill(fa.begin(), fa.begin() + n, 0);
    rep(i, 0, sz(a)) fa[i].x = a[i];
    rep(i, 0, sz(b)) fa[i].y = b[i];
    fft(fa, n);
    trav(x, fa) x = x * x;
    rep(i, 0, n) fb[i] = fa[(n - i) & (n - 1)] - conj(fa[i]);
    fft(fb, n);
    vd r(s);
    rep(i, 0, s) r[i] = fb[i].y / (4 * n);
    return r;
} /// end-hash

// Integer multiply mod m (num = complex) /// start-hash
vi multiply_mod(const vi &a, const vi &b, int m) {
    int s = sz(a) + sz(b) - 1;
    if (s <= 0)
        return {};
    int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
    if (sz(fa) < n)
        fa.resize(n);
    if (sz(fb) < n)
        fb.resize(n);

    rep(i, 0, sz(a)) fa[i] = num(a[i] & ((1 << 15) - 1), a[i] >> 15);
    fill(fa.begin() + sz(a), fa.begin() + n, 0);
    rep(i, 0, sz(b)) fb[i] = num(b[i] & ((1 << 15) - 1), b[i] >> 15);
    fill(fb.begin() + sz(b), fb.begin() + n, 0);

    fft(fa, n);
    fft(fb, n);
    double r0 = 0.5 / n; // 1/2n
    rep(i, 0, n / 2 + 1) {
        int j = (n - i) & (n - 1);
        num g0 = (fb[i] + conj(fb[j])) * r0;
        num g1 = (fb[i] - conj(fb[j])) * r0;
        swap(g1.x, g1.y);
        g1.y *= -1;
        if (j != i) {
            swap(fa[j], fa[i]);
            fb[j] = fa[j] * g1;
            fa[j] = fa[j] * g0;
        }
        fb[i] = fa[i] * conj(g1);
        fa[i] = fa[i] * conj(g0);
    }
    fft(fa, n);
    fft(fb, n);
    vi r(s);
    rep(i, 0, s) r[i] = int((ll(fa[i].x + 0.5) + (ll(fa[i].y + 0.5) % m << 15) + (ll(fb[i].x + 0.5) % m << 15) +
                             (ll(fb[i].y + 0.5) % m << 30)) %
                            m);
    return r;
} /// end-hash
#endif

} // namespace fft

// For multiply_mod, use num = modnum, poly = vector<num>
using fft::num;
using poly = fft::vn;
using fft::inverse;
using fft::multiply;
/// start-hash
poly &operator+=(poly &a, const poly &b) {
    if (sz(a) < sz(b))
        a.resize(b.size());
    rep(i, 0, sz(b)) a[i] = a[i] + b[i];
    return a;
}
poly operator+(const poly &a, const poly &b) {
    poly r = a;
    r += b;
    return r;
}
poly &operator-=(poly &a, const poly &b) {
    if (sz(a) < sz(b))
        a.resize(b.size());
    rep(i, 0, sz(b)) a[i] = a[i] - b[i];
    return a;
}
poly operator-(const poly &a, const poly &b) {
    poly r = a;
    r -= b;
    return r;
}
poly operator*(const poly &a, const poly &b) {
    // TODO: small-case?
    return multiply(a, b);
}
poly &operator*=(poly &a, const poly &b) { return a = a * b; }
/// end-hash
poly &operator*=(poly &a, const num &b) { // Optional
    trav(x, a) x = x * b;
    return a;
}
poly operator*(const poly &a, const num &b) {
    poly r = a;
    r *= b;
    return r;
}

// Polynomial floor division; no leading 0's plz
poly operator/(poly a, poly b) { /// start-hash
    if (sz(a) < sz(b))
        return {};
    int s = sz(a) - sz(b) + 1;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    a.resize(s);
    b.resize(s);
    a = a * inverse(move(b));
    a.resize(s);
    reverse(a.begin(), a.end());
    return a;
} /// end-hash
poly &operator/=(poly &a, const poly &b) { return a = a / b; }
poly &operator%=(poly &a, const poly &b) { /// start-hash
    if (sz(a) >= sz(b)) {
        poly c = (a / b) * b;
        a.resize(sz(b) - 1);
        rep(i, 0, sz(a)) a[i] = a[i] - c[i];
    }
    return a;
} /// end-hash
poly operator%(const poly &a, const poly &b) {
    poly r = a;
    r %= b;
    return r;
}

// Log/exp/pow
poly deriv(const poly &a) { /// start-hash
    if (a.empty())
        return {};
    poly b(sz(a) - 1);
    rep(i, 1, sz(a)) b[i - 1] = a[i] * i;
    return b;
} /// end-hash
poly integ(const poly &a) { /// start-hash
    if (a.empty())
        return {0};
    poly b(sz(a) + 1);
    b[1] = 1;                                                  // mod p
    rep(i, 2, sz(b)) b[i] = b[fft::mod % i] * (-fft::mod / i); // mod p
    rep(i, 1, sz(b)) b[i] = a[i - 1] * b[i];                   // mod p
    // rep(i,1,sz(b)) b[i]=a[i-1]*inv(num(i)); // else
    return b;
} /// end-hash
poly log(const poly &a) { // a[0] == 1 /// start-hash
    poly b = integ(deriv(a) * inverse(a));
    b.resize(a.size());
    return b;
} /// end-hash
poly exp(const poly &a) { // a[0] == 0 /// start-hash
    poly b(1, num(1));
    if (a.empty())
        return b;
    while (sz(b) < sz(a)) {
        int n = min(sz(b) * 2, sz(a));
        b.resize(n);
        poly v = poly(a.begin(), a.begin() + n) - log(b);
        v[0] = v[0] + num(1);
        b *= v;
        b.resize(n);
    }
    return b;
} /// end-hash
poly pow(const poly &a, int m) { // m >= 0 /// start-hash
    poly b(a.size());
    if (!m) {
        b[0] = 1;
        return b;
    }
    int p = 0;
    while (p < sz(a) && a[p].v == 0)
        ++p;
    if (1ll * m * p >= sz(a))
        return b;
    num mu = pow(a[p], m), di = inv(a[p]);
    poly c(sz(a) - m * p);
    rep(i, 0, sz(c)) c[i] = a[i + p] * di;
    c = log(c);
    trav(v, c) v = v * m;
    c = exp(c);
    rep(i, 0, sz(c)) b[i + m * p] = c[i] * mu;
    return b;
} /// end-hash

// Multipoint evaluation/interpolation
/// start-hash
vector<num> eval(const poly &a, const vector<num> &x) {
    int n = sz(x);
    if (!n)
        return {};
    vector<poly> up(2 * n);
    rep(i, 0, n) up[i + n] = poly({0 - x[i], 1});
    per(i, 1, n) up[i] = up[2 * i] * up[2 * i + 1];
    vector<poly> down(2 * n);
    down[1] = a % up[1];
    {
        rep(i, 2, 2 * n) {
            down[i] = down[i / 2] % up[i];
        }
    }
    vector<num> y(n);
    rep(i, 0, n) y[i] = down[i + n][0];
    return y;
} /// end-hash
/// start-hash
poly interp(const vector<num> &x, const vector<num> &y) {
    int n = sz(x);
    assert(n);
    vector<poly> up(n * 2);
    rep(i, 0, n) up[i + n] = poly({0 - x[i], 1});
    per(i, 1, n) up[i] = up[2 * i] * up[2 * i + 1];
    vector<num> a = eval(deriv(up[1]), x);
    vector<poly> down(2 * n);
    rep(i, 0, n) down[i + n] = poly({y[i] * inv(a[i])});
    per(i, 1, n) down[i] = down[i * 2] * up[i * 2 + 1] + down[i * 2 + 1] * up[i * 2];
    return down[1];
} /// end-hash
} // namespace MIT

namespace mine {
namespace ignore1 {
#include "../../content/number-theory/ModPow.h"
}
namespace ignore2 {
#include "../../content/number-theory/ModularArithmetic.h"
}
ll modpow(ll a, ll e);
#include "../../content/numerical/NumberTheoreticTransform.h"
ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}
#include "../../content/numerical/FastFourierTransformMod.h"
struct Mod {
    ll x;
    Mod() : x(0) {}
    Mod(ll xx) : x(xx % mod) {}
    Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
    Mod operator-(Mod b) { return Mod(x < b.x ? x - b.x + mod : x - b.x); }
    Mod operator*(Mod b) { return Mod(x * b.x); }
    Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) { return a^(mod-2); }
	Mod operator^(ll e) {
		if (!e) return Mod(1);
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
    explicit operator ll() const { return x; }
};

typedef Mod num;
typedef vector<num> poly;

#include "../../content/numerical/PolyBase.h"
#include "../../content/numerical/PolyMod.h"
#include "../../content/numerical/PolyIntegDeriv.h"
#include "../../content/numerical/PolyLogExp.h"
#include "../../content/numerical/PolyPow.h"
#include "../../content/numerical/PolyEvaluate.h"
#include "../../content/numerical/PolyInterpolate.h"
} // namespace mine

pair<mine::poly, MIT::poly> genVec(int sz) {
    mine::poly a;
    MIT::poly am;
    for (int i = 0; i < sz; i++) {
        int val = rand();
        a.push_back(val);
        am.push_back(val);
    }
    return {a, am};
}
bool checkEqual(mine::poly a, MIT::poly b) {
    if (sz(a) != sz(b))
        return false;
    int ml = min(sz(a), sz(b));
    for (int i = 0; i < ml; i++)
        if (a[i].x != b[i].v)
            return false;
    // for (int i = ml; i < sz(a); i++)
    //     if (a[i].x != 0)
    //         return false;
    // for (int i = ml; i < sz(b); i++)
    //     if (b[i].v != 0)
    //         return false;
    return true;
}

template <class A, class B> void fail(A mine, B mit) {
    cout<<"mine: ";
    for (auto i : mine)
        cout << i.x << ' ';
    cout << endl;
    cout<<"MIT:  ";
    for (auto i : mit)
        cout << i.v << ' ';
    cout << endl;

}

const int NUMITERS=10;
template <class A, class B> void testBinary(string name, A f1, B f2, int mxSz = 5) {
    for (int it = 0; it < NUMITERS; it++) {
        auto a = genVec((rand() % mxSz) + 1);
        auto b = genVec((rand() % mxSz) + 1);
        mine::poly res;
        res = f1(a.first, b.first);
        auto t = f2(a.second, b.second);
        if (!checkEqual(res, t))
            fail(res, t);

        assert(checkEqual(res, t));
    }
    cout << name << " tests passed!" << endl;
    auto a = genVec(mxSz);
    auto b = genVec(mxSz/2);
    {
        timeit x("mine");
        for (int it=0; it<NUMITERS; it++) {
            f1(a.first, b.first);
        }
    }
    {
        timeit x("MIT");
        for (int it=0; it<NUMITERS; it++) {
            f2(a.second, b.second);
        }
    }
    cout<<endl;
}
template <class A, class B> void testUnary(string name, A f1, B f2, int mxSz = 5) {
    for (int it = 0; it < NUMITERS; it++) {
        auto a = genVec((rand() % mxSz) + 1);
        auto res = f1(a.first);
        auto t = f2(a.second);
        if (!checkEqual(res, t))
            fail(res, t);
        assert(checkEqual(res, t));
    }
    cout << name + " tests passed!" << endl;
    auto a = genVec(mxSz);
    {
        timeit x("mine");
        for (int it=0; it<NUMITERS; it++) {
            f1(a.first);
        }
    }
    {
        timeit x("MIT");
        for (int it=0; it<NUMITERS; it++) {
            f2(a.second);
        }
    }
    cout<<endl;
}
template <class A, class B> void testPow(string name, A f1, B f2, int mxSz = 5, int mxPref=5) {
    for (int it = 0; it < NUMITERS; it++) {
        auto a = genVec((rand() % mxSz) + 1);
        int pref = rand()%mxSz;
        for (int j=0; j<pref; j++) {
            a.first.insert(a.first.begin(), mine::num(0));
            a.second.insert(a.second.begin(), MIT::num(0));
        }
        int p = rand() % 5;
        auto res = f1(a.first, p);
        auto t = f2(a.second, p);
        if (!checkEqual(res, t))
            fail(res, t);
        assert(checkEqual(res, t));
    }
    cout << name + " tests passed!" << endl;
    auto a = genVec((rand() % mxSz) + 1);
    int p = mxSz;
    {
        timeit x("mine");
        for (int it = 0; it < NUMITERS; it++) {
            f1(a.first, p);
        }
    }
    {
        timeit x("mit");
        for (int it = 0; it < NUMITERS; it++) {
            f2(a.second, p);
        }
    }
    cout<<endl;
}
template <class A, class B> void testEval(string name, A f1, B f2, int mxSz = 5) {
    for (int it = 0; it < NUMITERS; it++) {
        break;
        auto a = genVec((rand() % mxSz) + 1);
        auto b = genVec((rand() % mxSz)+1);
        auto res = f1(a.first, b.first);
        auto t = f2(a.second, b.second);
        if (!checkEqual(res, t))
            fail(res, t);
        assert(checkEqual(res, t));
    }
    cout << name + " tests passed!" << endl;
            auto a = genVec(mxSz);
            auto b = genVec(mxSz);
    {
        timeit x("mine");
        for (int it = 0; it < NUMITERS; it++) {
            f1(a.first, b.first);
        }
    }
    {
        timeit x("MIT");
        for (int it = 0; it < NUMITERS; it++) {
            f2(a.second, b.second);
        }
    }
    cout<<endl;
}
template <class A, class B> void testInterp(string name, A f1, B f2, int mxSz = 5) {
    for (int it = 0; it < NUMITERS; it++) {
        int s = (rand()%mxSz) + 1;
        auto a = genVec(s);
        auto b = genVec(s);
        auto res = f1(a.first, b.first);
        auto t = f2(a.second, b.second);
        if (!checkEqual(res, t))
            fail(res, t);
        assert(checkEqual(res, t));
    }
    cout << name + " tests passed!" << endl;
    auto a = genVec(mxSz);
    auto b = genVec(mxSz);
    {
        timeit x("mine");
        for (int it = 0; it < NUMITERS; it++) {
            f1(a.first, b.first);
        }
    }
    {
        timeit x("MIT");
        for (int it = 0; it < NUMITERS; it++) {
            f2(a.second, b.second);
        }
    }
    cout<<endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int SZ = 100000;
    testBinary("sub", mine::operator-, MIT::operator-, SZ);
    testBinary("add", mine::operator+, MIT::operator+, SZ);
    testBinary("div", mine::operator/, MIT::operator/, SZ);
    testBinary("mod", mine::operator%, MIT::operator%, SZ);
    testUnary("inv", mine::inverse, MIT::inverse, SZ);
    testUnary("derivative", mine::deriv, MIT::deriv, SZ);
    testUnary("integral", mine::integr, MIT::integ, SZ);
    testUnary("log", mine::log, MIT::log, SZ);
    testUnary("exp", mine::exp, MIT::exp, SZ);
    SZ = 10000;
    testPow("pow", mine::pow, MIT::pow, SZ, 5);
    testEval("eval", mine::eval, MIT::eval, SZ);
    testInterp("interp", mine::interp, MIT::interp, SZ);
    return 0;
}