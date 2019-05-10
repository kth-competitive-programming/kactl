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
const int n = 128;
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
    double Tlimit, pk=0;
    struct Vertex {
        int i, d;
        Vertex(int i) : i(i), d(0) {}
    };
    typedef vector<Vertex> vv;
    vv V;
    vector<vi> C;
    vi qmax, Q, S, So;
    bool cut1(const int pi, const vi &A) {
        trav(i, A) if (e[pi][i]) return true;
        return false;
    }
    void color_sort(vv &R) {
        int j = 0, mxk = 1, mnk = max(sz(qmax) - sz(Q) + 1, 1);
        C[1].clear(), C[2].clear();
        trav(v, R) {
            int k = 1;
            while (cut1(v.i, C[k])) k++;
            if (k > mxk) mxk = k, C[mxk + 1].clear();
            C[k].push_back(v.i);
            if (k < mnk) R[j++].i = v.i;
        }
        if (j > 0) R[j - 1].d = 0;
        rep(k,mnk,mxk + 1) trav(i, C[k]) R[j].i = i, R[j++].d = k;
    }
    void init(vv &r) {
		trav(i,r) i.d = 0;
        trav(i, r) trav(j, r) i.d += e[i.i][j.i];
        sort(all(r), [](auto a, auto b) { return a.d > b.d; });
    }
    void expand_dyn(vv &R, int lev = 1) {
        S[lev] += S[lev - 1] - So[lev];
        So[lev] = S[lev - 1];
        while (sz(R)) {
			if (sz(Q) + R.back().d <= sz(qmax)) return;
			Q.push_back(R.back().i);
			vv Rp;
			rep(i,0,sz(R)-1) if (e[R.back().i][R[i].i]) Rp.push_back(R[i].i);
			if (sz(Rp)) {
				if (S[lev] / ++pk < Tlimit) init(Rp);
				color_sort(Rp), S[lev]++;
				expand_dyn(Rp, lev + 1);
			} else if (sz(Q) > sz(qmax))
				qmax = Q;
			Q.pop_back(), R.pop_back();
        }
    }
    vi mcqdyn() {
        init(V);
        int max_degree = V[0].d;
        rep(i,0,sz(V)) V[i].d = min(i, max_degree) + 1;
        expand_dyn(V);
        return qmax;
    }
    Maxclique(vector<B> conn, double tt = 0.025) : e(conn), Tlimit(tt), S(sz(e)), So(S), C(sz(e) + 1) {
        rep(i,0,sz(e)) V.push_back(Vertex(i));
    }
};

int main2() {
    int iters = 1000;
    {
        srand(0);
        timeit x("sjtu");
        rep(it, 0, 10) {
            vector<B> ed(n);
            bool eda[n][n];
            int ind[n] = {};
            rep(i, 0, n) rep(j, 0, i) {
                ed[i][j] = (rand() % 100) < 95;
                ed[j][i] = ed[i][j];
                eda[i][j] = ed[i][j];
                eda[j][i] = ed[j][i];
            }
            auto clique2 = new Maxclique(ed, 0.025);
            cout << sz(clique2->mcqdyn()) << endl;
        }
        cout << endl;
    }
    {
        srand(0);
        timeit x("sjtu");
        rep(it, 0, iters) {
            cout << it << endl;
            vector<B> ed(n);
            bool eda[n][n];
            int ind[n] = {};
            rep(i, 0, n) rep(j, 0, i) {
                ed[i][j] = (rand() % 100) < 95;
                ed[j][i] = ed[i][j];
                eda[i][j] = ed[i][j];
                eda[j][i] = ed[j][i];
            }
            auto clique = new Maxclique(ed, 0.0);
            auto clique2 = new Maxclique(ed, 0.025);
            auto clique3 = new sjtu::Maxclique(eda, n, 0.0);
            auto sz1 = sz(clique->mcqdyn()), sz2 = sz(clique2->mcqdyn());
            int res[n], sz3;
            clique3->mcqdyn(res, sz3);
            assert(sz1 == sz2 && sz2 == sz3);
        }
        cout << endl;
    }
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
