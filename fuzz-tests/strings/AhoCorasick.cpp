#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/strings/AhoCorasick.h"

template<class F>
void gen(string& s, int at, int alpha, F f) {
	if (at == sz(s)) f();
	else {
		rep(i,0,alpha) {
			s[at] = (char)('A' + i);
			gen(s, at+1, alpha, f);
		}
	}
}

void test(const string& s) {
	vector<string> pats;
	string cur;
	rep(i,0,sz(s)) {
		if (s[i] == 'A') {
			pats.push_back(cur);
			cur = "";
		}
		else cur += s[i];
	}

	string hay = cur;
	trav(x, pats) if (x.empty()) return;

	// Priority order of patterns for findAll: shorter patterns first, tie-broken by index
	vi order(sz(pats));
	iota(all(order), 0);
	stable_sort(all(order), [&](int a, int b) { return sz(pats[a]) < sz(pats[b]); });

	AhoCorasick ac(pats);
	vector<vi> positions = ac.findAll(pats, hay);

	vi ord;
	rep(i,0,sz(hay)) {
		ord.clear();
		trav(j, order) {
			string& pat = pats[j];
			if (hay.substr(i, pat.size()) == pat) {
				ord.push_back(j);
			}
		}

		if (positions[i] != ord) {
			cerr << "failed!" << endl;
			cerr << hay << endl;
			trav(x, pats) cerr << x << endl;
			cerr << "failed at position " << i << endl;
			cerr << "got:" << endl;
			trav(x, positions[i]) cerr << x << ' ';
			cerr << endl;
			cerr << "expected:" << endl;
			trav(x, ord) cerr << x << ' ';
			cerr << endl;
			abort();
		}
	}
}

int main() {
	// test ~4^11 strings
	rep(n,0,12) {
		string s(n, 'x');
		gen(s, 0, 4, [&]() {
			test(s);
		});
	}
	// then ~5^8
	rep(n,0,9) {
		string s(n, 'x');
		gen(s, 0, 5, [&]() {
			test(s);
		});
	}
	cout<<"Tests passed!"<<endl;
}
