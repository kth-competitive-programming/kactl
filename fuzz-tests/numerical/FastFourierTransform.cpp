#include <bits/stdc++.h>
#include <valarray>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef valarray<complex<double> > carray;
void fft(carray& x, carray& roots) {
	int N = sz(x);
	if (N <= 1) return;
	carray even = x[slice(0, N/2, 2)];
	carray odd = x[slice(1, N/2, 2)];
	carray rs = roots[slice(0, N/2, 2)];
	fft(even, rs);
	fft(odd, rs);
	rep(k,0,N/2) {
		auto t = roots[k] * odd[k];
		x[k    ] = even[k] + t;
		x[k+N/2] = even[k] - t;
	}
}

typedef vector<double> vd;
vd conv(const vd& a, const vd& b) {
	int s = sz(a) + sz(b) - 1, L = 32-__builtin_clz(s), n = 1<<L;
	if (s <= 0) return {};
	carray av(n), bv(n), roots(n);
	rep(i,0,n) roots[i] = polar(1.0, -2 * M_PI * i / n);
	copy(all(a), begin(av)); fft(av, roots);
	copy(all(b), begin(bv)); fft(bv, roots);
	roots = roots.apply(conj);
	carray cv = av * bv; fft(cv, roots);
	vd c(s); rep(i,0,s) c[i] = cv[i].real() / n;
	return c;
}

const double eps = 1e-8;
int main() {
	int n = 8;
	carray a(n), av(n), roots(n);
	rep(i,0,n) a[i] = rand() % 10 - 5;
	rep(i,0,n) roots[i] = polar(1.0, -2 * M_PI * i / n);
	av = a;
	fft(av, roots);
	rep(k,0,n) {
		complex<double> sum{};
		rep(x,0,n) {
			sum += a[x] * polar(1.0, -2 * M_PI * k * x / n);
		}
		auto diff = sum-av[k];
		assert(abs(diff.imag()) < eps && abs(diff.real()) < eps);
	}
	cout<<"Tests passed!"<<endl;
}
