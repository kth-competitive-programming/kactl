#include "../utilities/template.h"

#include "../../content/geometry/ConvexHull.h"
#include "../utilities/bench.h"

namespace old {
pair<vi, vi> ulHull(const vector<P>& S) {
	vi Q(sz(S)), U, L;
	iota(all(Q), 0);
	sort(all(Q), [&S](int a, int b){ return S[a] < S[b]; });
	for(auto &it: Q) {
#define ADDP(C, cmp) while (sz(C) > 1 && S[C[sz(C)-2]].cross(\
	S[it], S[C.back()]) cmp 0) C.pop_back(); C.push_back(it);
		ADDP(U, <=); ADDP(L, >=);
	}
	return {U, L};
}

vi convexHull(const vector<P>& S) {
	vi u, l; tie(u, l) = ulHull(S);
	if (sz(S) <= 1) return u;
	if (S[u[0]] == S[u[1]]) return {0};
	l.insert(l.end(), u.rbegin()+1, u.rend()-1);
	return l;
}
}

int main() {
    const int SZ = 1e2;
    rep(t,0,100000) {
        const int GRID=1e3;
        vector<P> pts(SZ);
        rep(i,0,SZ) pts[i] = P(rand()%GRID, rand()%GRID);
        auto res = convexHull(pts);
        auto res2 = old::convexHull(pts);
        assert(sz(res) == sz(res2));
        rep(i,0,sz(res2)) {
            assert(pts[res2[i]] == res[i]);
        }
    }
    cout<<"Tests passed!"<<endl;
}
