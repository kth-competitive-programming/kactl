/**
 * Author: tfg, Aeren, pajenegod, chilli
 * Date: 2020-04-15
 * License: CC0
 * Source:
 * Description:
 * Time:
 * Status:
 */
struct Matroid {
    bool check(int x) {} // will adding x make matroid dependent
    void add(int x) {} // adds x to matroid
    void clear() {}  // resets matroid to empty
};
template <class M1, class M2, class T> struct MatroidIsect {
	int n;
	vector<T> gset; vector<bool> iset;
	vector<M1> m1; vector<M2> m2;
	MatroidIsect(M1 m1, M2 m2, vector<T> gset) :
	 n(sz(gset)),gset(gset), iset(n+1), m1(n+1,m1), m2(n+1,m2) {}
	vector<T> solve() {
		iset[n] = true; // Add greedily
		rep(i,0,n) if (test(m1, i, n) && test(m2, i, n)) {
			iset[i] = true;
			m1[n].insert(gset[i]), m2[n].insert(gset[i]);
		}
		while (augment());
		vector<T> ans;
		rep(i,0,n) if (iset[i]) ans.push_back(gset[i]);
		return ans;
	}
	template <class M>
	bool test(vector<M> &m, int add, int rem) {
		return !iset[add] && iset[rem] && m[rem].check(gset[add]);
	}
	bool augment() {
		rep(i,0,n + 1) { //  Construct matroids
			if (iset[i]) {
				m1[i].clear(), m2[i].clear();
				rep(v, 0, n) if (v != i && iset[v])
				 m1[i].add(gset[v]), m2[i].add(gset[v]);
			}
		}
		queue<int> q({n});
		vector<int> frm(n + 1, -1);
		while (!q.empty()) { // Augment path
			int on = q.front(); q.pop();
			rep(v,0,n+1) if (frm[v] == -1 &&
					(test(m1, v, on) || test(m2, on, v))) {
				if (v == n) {
					while (on != n)
						iset[on] = !iset[on], on = frm[on];
					return true;
				}
				q.push(v), frm[v] = on;
			}
		}
		return false;
	}
};