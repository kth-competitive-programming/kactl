/**
 * Author: chilli, SJTU
 * Date: 2019-05-10
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/MaxCliqueDyn_maximum_clique_algorithm, https://github.com/FTRobbin/Dreadnought-Standard-Code-Library/blob/11c861e55a73be9c32a799bfe4398e0c62c2da15/improve/MaximumClique.cpp
 * Description: Finds a maximum clique of a graph (given as n x n symmetric
 * bitset matrix; self-edges not allowed). Can be used to find a maximum
 * independent set by finding a clique of a complement graph.
 * Time: Runs in about ~1s for n=155 and worst case random graphs (p=.95). Runs
 * faster for sparse graphs.
 * Status: fuzz-tested
 */
typedef bitset<200> B;
struct Maxclique {
	double limit=0.025, pk=0;
	struct Vertex { int i, d=0; };
	typedef vector<Vertex> vv;
	vector<B> e;
	vv V;
	vector<vi> C;
	vi qmax, q, S, So;
	bool cut1(int pi, vi& A) {
		trav(i, A) if (e[pi][i]) return true;
		return false;
	}
	void init(vv& r) {
		trav(v,r) v.d = 0;
		trav(v, r) trav(j, r) v.d += e[v.i][j.i];
		sort(all(r), [](auto a, auto b) { return a.d > b.d; });
		int mxD = r[0].d;
		rep(i,0,sz(r)) r[i].d = min(i, mxD) + 1;
	}
	void expand(vv& R, int lev = 1) {
		S[lev] += S[lev - 1] - So[lev];
		So[lev] = S[lev - 1];
		while (sz(R)) {
			if (sz(q) + R.back().d <= sz(qmax)) return;
			q.push_back(R.back().i);
			vv Rp;
			trav(v,R) if (e[R.back().i][v.i]) Rp.push_back({v.i});
			if (sz(Rp)) {
				if (S[lev]++ / ++pk < limit) init(Rp);
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
	Maxclique(vector<B> conn) :
		e(conn), C(sz(e) + 1), S(sz(e)), So(sz(e))  {
		rep(i,0,sz(e)) V.push_back({i});
	}
};
