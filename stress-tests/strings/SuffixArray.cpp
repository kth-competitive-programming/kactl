#include "../utilities/template.h"

#include "../../content/strings/SuffixArray.h"

struct VecSuffixArray {
	vi sa, lcp;
	VecSuffixArray(vi &s, int lim = 256) {
		int n = sz(s), k = 0;
		vi x(2 * n), y(2 * n), wv(n), ws(max(n, lim)), rank(n);
		sa = lcp = rank;
		rep(i,0,n) ws[x[i] = s[i]]++;
		rep(i,1,lim) ws[i] += ws[i - 1];
		for (int i = n; i--;) sa[--ws[x[i]]] = i;
		for (int j = 1, p = 0; p < n; j *= 2, lim = p) {
			p = 0;
			rep(i,n-j,n) y[p++] = i;
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			rep(i,0,n) wv[i] = x[y[i]];
			rep(i,0,lim) ws[i] = 0;
			rep(i,0,n) ws[wv[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[wv[i]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) {
				int a = sa[i-1], b = sa[i]; x[b] =
					y[a] == y[b] && y[a + j] == y[b + j] ? p - 1 : p++;
			}
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++) ;
	}
};

string display(const string& s) {
	string ret;
	for(auto &x: s) ret += (char)('a' + x - 1);
	return ret;
}

template<class F>
void gen(string& s, int at, int alpha, F f) {
	if (at == sz(s)) f();
	else {
		rep(i,0,alpha) {
			s[at] = (char)(i + 1);
			gen(s, at+1, alpha, f);
		}
	}
}

void test(const string& s, int alpha) {
	// cout << display(s) << endl;
	string copy = s;
	SuffixArray sa(copy, alpha+1);
	vi suffixes(sz(s)+1), lcp(sz(s)+1);
	iota(all(suffixes), 0);
	sort(all(suffixes), [&](int a, int b) {
		return s.substr(a) < s.substr(b);
	});

	if (suffixes != sa.sa) {
		cout << "sa fails for " << display(s) << ' ' << alpha << endl;
		assert(suffixes == sa.sa);
	}

	rep(i,0,sz(s)) {
		int j = 0;
		while (max(j + suffixes[i], suffixes[i+1]) < sz(s) &&
				s[j + suffixes[i]] == s[j + suffixes[i+1]])
			j++;
		lcp[i+1] = j;
	}

	if (lcp != sa.lcp) {
		cout << "lcp fails for " << display(s) << ' ' << alpha << endl;
		assert(lcp == sa.lcp);
	}
}

const int MAXN = 1e5;
namespace old {
typedef long long ll;
typedef pair<ll, int> pli;
void count_sort(vector<pli> &b, int bits) { // (optional)
	// this is just 3 times faster than stl sort for N=10^6
	int mask = (1 << bits) - 1;
	for (int it = 0; it < 2; it++) {
		int move = it * bits;
		vector<int> q(1 << bits), w((q).size() + 1);
		for (int i = 0; i < sz(b); i++)
			q[(b[i].first >> move) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pli> res(b.size());
		for (int i = 0; i < sz(b); i++)
			res[w[(b[i].first >> move) & mask]++] = b[i];
		swap(b, res);
	}
}
struct SuffixArray {
	vector<int> a;
	string s;
	SuffixArray(const string &_s) : s(_s + '\0') {
		int N = sz(s);
		vector<pli> b(N);
		a.resize(N);
		for (int i = 0; i < N; i++) {
			b[i].first = s[i];
			b[i].second = i;
		}

		int q = 8;
		while ((1 << q) < N)
			q++;
		for (int moc = 0;; moc++) {
			count_sort(b, q); // sort(all(b)) can be used as well
			a[b[0].second] = 0;
			for (int i = 1; i < N; i++)
				a[b[i].second] = a[b[i - 1].second] + (b[i - 1].first != b[i].first);

			if ((1 << moc) >= N)
				break;
			for (int i = 0; i < N; i++) {
				b[i].first = (ll)a[i] << q;
				if (i + (1 << moc) < N)
					b[i].first += a[i + (1 << moc)];
				b[i].second = i;
			}
		}
		for (int i = 0; i < sz(a); i++)
			a[i] = b[i].second;
	}
	vector<int> lcp() {
		// longest common prefixes: res[i] = lcp(a[i],
		// a[i-1])
		int n = sz(a), h = 0;
		vector<int> inv(n), res(n);
		for (int i = 0; i < n; i++)
			inv[a[i]] = i;
		for (int i = 0; i < n; i++)
			if (inv[i] > 0) {
				int p0 = a[inv[i] - 1];
				while (s[i + h] == s[p0 + h])
					h++;
				res[inv[i]] = h;
				if (h > 0)
					h--;
			}
		return res;
	}
};
} // namespace kactl

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

signed compare() {
	srand(0);
	vi vS;
	string S;
	for (int iter = 0; iter < 5; iter++) {

		for (int i = 0; i < MAXN; i++) {
			int t = rand() % 2;
			vS.push_back(t + 1);
			S.push_back((char)(t + 'a'));
		}

		// cout << S << endl;
		vector<array<int, 2>> res;
		{
			timeit x("kactl");
			old::SuffixArray kactl(S);
			// cout << kactl.a[100] << endl;
			auto lcp = kactl.lcp();
			rep(i,0,sz(S)+1)
				res.push_back({kactl.a[i], lcp[i]});
		}
		{
			timeit x("MIT");
			SuffixArray sa(S);
			// cout << sa.sa[100] << endl;
			rep(i,0,sz(S)+1) {
				assert((res[i] == array<int, 2>{sa.sa[i], sa.lcp[i]}));
			}
		}
	}
	return 0;
}

void stress(bool onlySmall = false) {
	rep(large,0,2) {
		if (onlySmall && large) break;
		double work = large ? 1e7 : 5e5;
		rep(alpha,1,27) {
			rep(n,0,100) {
				if (n * n * pow(alpha, n) > work) break;
				// cout << alpha << ' ' << n << ": " << flush;
				string s(n, 'x');
				gen(s, 0, alpha, [&]() {
					test(s, alpha);
				});
			}
		}
	}
}

void perf() {
	string str;
	rep(i,0,300'000)
		str += (char)('a' + (rand() % 10));
	ll res = 0;
	rep(i,0,30) {
		SuffixArray sa(str);
		res += sa.sa[0];
	}
	cout << res << endl;
}

void perf2() {
	vi str;
	rep(i,0,300'000)
		str.push_back(1 + (rand() % 100'000));
	str.push_back(0);
	ll res = 0;
	rep(i,0,30) {
		VecSuffixArray sa(str, 101'000);
		res += sa.sa[0];
	}
	cout << res << endl;
}

int main() {
	// compare();
	stress(0);
	cout<<"Tests passed!"<<endl;
	// perf();
	// perf2();
}
