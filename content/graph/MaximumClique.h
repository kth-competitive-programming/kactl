/**
 * Author: chilli, Haobin Ni
 * Date: 2019-05-10
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/MaxCliqueDyn_maximum_clique_algorithm
 * Description: Finds the maximum clique of a graph. Can be used to find the
 * maximum independent set by finding the clique of the complement graph.
 * Time: Runs in about ~1s for n=155 and worst case random graphs (p=.95). Runs
 * faster for sparse graphs.
 * Status: fuzz-tested
 */
struct Maxclique {
	double Tlimit=0.025, pk=0;
	struct Vertex { int i, d; Vertex(int i) : i(i), d(0) {} };
	typedef vector<Vertex> vv;
	vector<B> e;
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