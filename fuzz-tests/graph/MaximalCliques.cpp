#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// #include "../../content/graph/MaximalCliques.h"
const int n=128;
typedef bitset<n> B;
template<class F>
void cliques(vector<B>& eds, F f, B P = ~B(), B X={}, B R={}) {
	if (!P.any()) { if (!X.any()) f(R); return; }
	auto q = (P | X)._Find_first();
	auto cands = P & ~eds[q];
	rep(i,0,sz(eds)) if (cands[i]) {
		R[i] = 1;
		cliques(eds, f, P & eds[i], X & eds[i], R);
		R[i] = P[i] = 0; X[i] = 1;
	}
}


int main1() {
	rep(n,1,11) rep(m,0,200) {
		vector<B> ed(n);
		rep(i,0,m) {
			int a = rand() % n, b = rand() % n;
			if (a == b) continue;
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
			rep(i,0,n) if (c[i])
			rep(j,i+1,n) if (c[j]) {
				if (!ed[i][j]) return false; // not a clique
			}
			rep(i,0,n) if (!c[i]) {
				bool all = true;
				rep(j,0,n) if (c[j]) all &= ed[i][j];
				if (all) return false; // not maximal
			}
			return true;
		};
		trav(c, cl) {
			assert(isClique(c));
		}

		int realCo = 0;
		rep(bi,0,(1 << n)) {
			B c{};
			rep(i,0,n) c[i] = !!(bi & (1 << i));
			if (isClique(c)) realCo++;
		}
		assert(co == realCo);
	}
	return 0;
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
	vector<B> e; int pk; const double Tlimit;
	struct Vertex{ int i, d; Vertex(int i):i(i),d(0){} };
	typedef vector<Vertex> vv;
	vv V; vector<vi> C; vi qmax, Q;
	static bool desc_degree(const Vertex &vi, const Vertex &vj){
		return vi.d > vj.d;
	}
	void set_degrees(vv &v){
		rep(i,0,sz(v)){
			v[i].d=0;
			rep(j,0,sz(v)) v[i].d += e[v[i].i][v[j].i];
		}
	}
	struct Step{ int i1, i2; Step():i1(0),i2(0){} };
	vector<Step> S;
	bool cut1(const int pi, const vi &A){
		rep(i,0,sz(A)) if (e[pi][A[i]]) return true;
		return false;
	}
	void expand(vv &R, int lev=1){// diff -> diff with no dyn
		S[lev].i1 = S[lev].i1 + S[lev - 1].i1 - S[lev].i2;//diff
		S[lev].i2 = S[lev - 1].i1;//diff
		while(sz(R)) {
			if(sz(Q) + R.back().d > sz(qmax)){
				Q.push_back(R.back().i); vv Rp;
				rep(i,0,sz(R)-1)
					if(e[R.back().i][R[i].i])
						Rp.push_back(R[i].i);
				if(sz(Rp)){
					if((double)S[lev].i1 / ++pk < Tlimit)
						set_degrees(R), sort(all(R), desc_degree);

					int j = 0, maxno = 1, min_k = max(sz(qmax) - sz(Q) + 1, 1);
					C[1].clear(), C[2].clear();
					rep(i,0,sz(Rp)){
						int pi = Rp[i].i, k = 1;
						while(cut1(pi, C[k])) k++;
						if(k > maxno) maxno = k, C[maxno + 1].clear();
						C[k].push_back(pi);
						if(k < min_k) Rp[j++].i = pi;
					}
					if(j > 0) Rp[j - 1].d = 0;
					rep(k,min_k, maxno+1)
						rep(i,0,sz(C[k]))
							Rp[j].i = C[k][i], Rp[j++].d = k;
					S[lev].i1++;
					expand(Rp, lev+1);
				}
				else if(sz(Q) > sz(qmax)) qmax = Q;
				Q.pop_back();
			}
			else return;
			R.pop_back();
		}
	}
	vector<int> mcqdyn(){
		set_degrees(V); sort(all(V), desc_degree);
		const int max_degree = V[0].d;
		rep(i,0,sz(V)) V[i].d = min(i, max_degree) + 1;
		expand(V);
		return qmax;
	}
	Maxclique(vector<B> conn, const double tt = 0.025): e(conn), pk(0), Tlimit(tt), C(sz(e)+1), S(sz(e)+1) {
		rep(i,0,sz(conn)) V.push_back(Vertex(i));
	}
};


int main2() {
	int iters=1000;
	{
		srand(0);
		timeit x("sjtu");
		rep(it,0,iters) {
			cout<<it<<endl;
			vector<B> ed(n);
			int ind[n] = {};
			rep(i,0,n) rep(j,0,i) {
				ed[i][j] = (rand()%100) < 95;
				ed[j][i] = ed[i][j];
			}
			auto clique = new Maxclique(ed, 0.0);
			auto clique2 = new Maxclique(ed, 0.025);
			// int co = 0, sum = 0, mx=0;
			// cliques(ed, [&](B x) { mx = max(mx, (int)x.count()); co++; sum += (int)x.count(); });
			// assert(sz(clique->mcqdyn()) == mx);
			assert(sz(clique->mcqdyn()) == sz(clique2->mcqdyn()));
		}
		cout<<endl;
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
