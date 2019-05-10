#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < int(b); ++i)
#define trav(a, v) for (auto &a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// #include "../../content/graph/MaximalCliques.h"
const int n = 63;
typedef bitset<n> B;
template <class F> void cliques(vector<B> &eds, F f, B P = ~B(), B X = {}, B R = {}) {
	if (!P.any()) {
		if (!X.any())
			f(R);
		return;
	}
	auto q = (P | X)._Find_first();
	auto cands = P & ~eds[q];
	rep(i, 0, sz(eds)) if (cands[i]) {
		R[i] = 1;
		cliques(eds, f, P & eds[i], X & eds[i], R);
		R[i] = P[i] = 0;
		X[i] = 1;
	}
}

int main1() {
	rep(n, 1, 11) rep(m, 0, 200) {
		vector<B> ed(n);
		rep(i, 0, m) {
			int a = rand() % n, b = rand() % n;
			if (a == b)
				continue;
			ed[a][b] = 1;
			ed[b][a] = 1;
		}
		unordered_set<B> cl;
		int co = 0;
		cliques(ed, [&](B x) {
			co++;
			cl.insert(x);
		});
		assert(sz(cl) == co); // no duplicates
		auto isClique = [&](B c) {
			rep(i, 0, n) if (c[i]) rep(j, i + 1, n) if (c[j]) {
				if (!ed[i][j])
					return false; // not a clique
			}
			rep(i, 0, n) if (!c[i]) {
				bool all = true;
				rep(j, 0, n) if (c[j]) all &= ed[i][j];
				if (all)
					return false; // not maximal
			}
			return true;
		};
		trav(c, cl) { assert(isClique(c)); }

		int realCo = 0;
		rep(bi, 0, (1 << n)) {
			B c{};
			rep(i, 0, n) c[i] = !!(bi & (1 << i));
			if (isClique(c))
				realCo++;
		}
		assert(co == realCo);
	}
	return 0;
}

namespace sjtu {
#include "sjtuclique.h"
}
namespace mit {
class clique {
  public:
  static const long long ONE = 1;
  static const long long MASK = (1 << 21) - 1;
  char* bits;
  int n, size, cmax[63];
  long long mask[63], cons;
  // initiate lookup table
  clique() {
    bits = new char[1 << 21];
    bits[0] = 0;
    for (int i = 1; i < (1<<21); ++i)
      bits[i] = bits[i >> 1] + (i & 1);
  }
  ~clique() {
    delete bits;
  }
  // search routine
  bool search(int step,int siz,ll mor,ll con);
  // solve maximum clique and return size
  int sizeClique(vector<vector<int> >& mat);
  // solve maximum clique and return set
  vector<int>getClq(vector<vector<int> >&mat);
};
// step is node id, size is current sol., more is available mask, cons is constitution mask
bool clique::search(int step, int size,
                    ll more, ll cons) {
  if (step >= n) {
    if (size > this->size) {
      // a new solution reached
      this->size = size;
      this->cons = cons;
    }
    return true;
  }
  long long now = ONE << step;
  if ((now & more) > 0) {
    long long next = more & mask[step];
    if (size + bits[next & MASK] +
        bits[(next >> 21) & MASK] +
        bits[next >> 42] >= this->size
     && size + cmax[step] > this->size) {
      // the current node is in the clique
      if (search(step+1,size+1,next,cons|now))
        return true;
    }
  }
  long long next = more & ~now;
  if (size + bits[next & MASK] +
      bits[(next >> 21) & MASK] +
      bits[next >> 42] > this->size) {
    // the current node is not in the clique
    if (search(step + 1, size, next, cons))
      return true;
  }
  return false;
}
// solve maximum clique and return size
int clique::sizeClique(vector<vector<int> >& mat) {
  n = mat.size();
  // generate mask vectors
  for (int i = 0; i < n; ++i) {
    mask[i] = 0;
    for (int j = 0; j < n; ++j)
      if (mat[i][j] > 0) mask[i] |= ONE << j;
  }
  size = 0;
  for (int i = n - 1; i >= 0; --i) {
    search(i + 1, 1, mask[i], ONE << i);
    cmax[i] = size;
  }
  return size;
}
// calls sizeClique and restore cons
vector<int> clique::getClq(
    vector<vector<int> >& mat) {
  sizeClique(mat);
  vector<int> ret;
  for (int i = 0; i < n; ++i)
    if ((cons&(ONE<<i)) > 0) ret.push_back(i);
  return ret;
}
}
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

struct Maxclique {
	vector<B> e;
	double Tlimit=0.025, pk=0;
	struct Vertex { int i, d; Vertex(int i) : i(i), d(0) {} };
	typedef vector<Vertex> vv;
	vv V;
	vector<vi> C;
	vi qmax, q, S, So;
	bool cut1(const int pi, const vi &A) {
		trav(i, A) if (e[pi][i]) return true;
		return false;
	}
	void init(vv &r) {
		trav(i,r) i.d = 0;
		trav(i, r) trav(j, r) i.d += e[i.i][j.i];
		sort(all(r), [](auto a, auto b) { return a.d > b.d; });
	}
	void expand(vv &R, int lev = 1) {
		S[lev] += S[lev - 1] - So[lev];
		So[lev] = S[lev - 1];
		while (sz(R)) {
			if (sz(q) + R.back().d <= sz(qmax)) return;
			q.push_back(R.back().i);
			vv Rp;
			trav(i,R) if (e[R.back().i][i.i]) Rp.push_back(i.i);
			if (sz(Rp)) {
				if (S[lev]++ / ++pk < Tlimit) init(Rp);
				int j = 0, mxk = 1, mnk = max(sz(qmax) - sz(q) + 1, 1);
				C[1].clear(), C[2].clear();
				trav(v, Rp) {
					int k = 1;
					while (cut1(v.i, C[k])) k++;
					if (k > mxk) mxk = k, C[mxk + 1].clear();
					if (k < mnk) Rp[j++].i = v.i;
					C[k].push_back(v.i);
				}
				if (j > 0) Rp[j - 1].d = 0;
				rep(k,mnk,mxk + 1) trav(i, C[k])
					Rp[j].i = i, Rp[j++].d = k;
				expand(Rp, lev + 1);
			} else if (sz(q) > sz(qmax)) qmax = q;
			q.pop_back(), R.pop_back();
		}
	}
	vi maxClique() { init(V), expand(V); return qmax; }
	Maxclique(vector<B> conn) : e(conn), S(sz(e)), So(S), C(sz(e) + 1) {
		rep(i,0,sz(e)) V.push_back(Vertex(i));
	}
};

int main2() {
	int iters = 1000;
	{
		srand(0);
		timeit x("sjtu");
		rep(it, 0, 1000) {
			vector<B> ed(n);
			bool eda[n][n];
			vector<vi> edi(n, vi(n));
			int ind[n] = {};
			rep(i, 0, n) rep(j, 0, i) {
				ed[i][j] = (rand() % 100) < 90;
				ed[j][i] = ed[i][j];
				eda[i][j] = ed[i][j];
				eda[j][i] = ed[j][i];
				edi[i][j] = ed[i][j];
				edi[j][i] = ed[j][i];
			}
			// auto mit = new mit::clique();
			// cout<<mit->sizeClique(edi)<<endl;
			auto clique2 = new Maxclique(ed);
			// cout << sz(clique2->maxClique()) << endl;
		}
		cout << endl;
	}
	// {
	// 	srand(0);
	// 	timeit x("sjtu");
	// 	rep(it, 0, iters) {
	// 		cout << it << endl;
	// 		vector<B> ed(n);
	// 		bool eda[n][n];
	// 		int ind[n] = {};
	// 		rep(i, 0, n) rep(j, 0, i) {
	// 			ed[i][j] = (rand() % 100) < 95;
	// 			ed[j][i] = ed[i][j];
	// 			eda[i][j] = ed[i][j];
	// 			eda[j][i] = ed[j][i];
	// 		}
	// 		auto clique2 = new Maxclique(ed);
	// 		auto clique3 = new sjtu::Maxclique(eda, n, 0.0);
	// 		auto sz2 = sz(clique2->maxClique());
	// 		int res[n], sz3;
	// 		clique3->mcqdyn(res, sz3);
	// 		assert(sz2 == sz3);
	// 	}
	// 	cout << endl;
	// }
	// {
	// 	srand(0);
	// 	timeit x("kactl");
	// 	rep(it,0,iters) {
	// 		vector<B> ed(n);
	// 		rep(i,0,n) rep(j,0,i) {
	// 			ed[i][j] = (rand()%100) < 95;
	// 			ed[j][i] = ed[i][j];
	// 		}
	// 		int co = 0, sum = 0, mx=0;
	// 		cliques(ed, [&](B x) { mx = max(mx, (int)x.count()); co++; sum += (int)x.count(); });
	// 		cout << co << ' ' << (double)sum / co << ' '<<mx<<endl;
	// 	}
	// 	cout<<endl;
	// }
	// {
	// 	srand(0);
	// 	timeit x("MIT");
	// 	rep(it,0,iters) {
	// 		clique mit;
	// 		vector<vector<int>> ed(n, vector<int>(n));
	// 		rep(i,0,n) rep(j,0,i) {
	// 			ed[i][j] = (rand()%100) < 95;
	// 			ed[j][i] = ed[i][j];
	// 		}
	// 		cout<< mit.sizeClique(ed)<<endl;
	// 	}
	// 	cout<<endl;
	// }
	return 0;
}

#ifndef target
#define target main2
#endif
int main() { target(); }
