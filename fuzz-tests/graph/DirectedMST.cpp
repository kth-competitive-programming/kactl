#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Bumpalloc {
	char buf[450 << 20];
	size_t bufp;
	void* alloc(size_t s) {
		assert(s < bufp);
		return (void*)&buf[bufp -= s];
	}
	Bumpalloc() { reset(); }

	template<class T> T* operator=(T&& x) {
		T* r = (T*)alloc(sizeof(T));
		new(r) T(move(x));
		return r;
	}
	void reset() { bufp = sizeof buf; }
} bumpalloc;

// When not testing perf, we don't want to leak memory
#ifndef TEST_PERF
#define new bumpalloc =
#endif
#include "../../content/graph/DirectedMST.h"
#ifndef TEST_PERF
#undef new
#endif

namespace mit {

#define N 110000
#define M 110000
#define inf 2000000000

struct edg {
    int u, v;
    int cost;
} E[M], E_copy[M];

int In[N], ID[N], vis[N], pre[N];

// edges pointed from root.
int Directed_MST(int root, int NV, int NE) {
    for (int i = 0; i < NE; i++)
        E_copy[i] = E[i];
    int ret = 0;
    int u, v;
    while (true) {
        rep(i,0,NV)   In[i] = inf;
        rep(i,0,NE) {
            u = E_copy[i].u;
            v = E_copy[i].v;
            if(E_copy[i].cost < In[v] && u != v) {
                In[v] = E_copy[i].cost;
                pre[v] = u;
            }
        }
        rep(i,0,NV) {
            if(i == root)   continue;
            if(In[i] == inf)    return -1; // no solution
        }

        int cnt = 0;
        rep(i,0,NV) {
            ID[i] = -1;
            vis[i] = -1;
        }
        In[root] = 0;

        rep(i,0,NV) {
            ret += In[i];
            int v = i;
            while(vis[v] != i && ID[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && ID[v] == -1) {
                for(u = pre[v]; u != v; u = pre[u]) {
                    ID[u] = cnt;
                }
                ID[v] = cnt++;
            }
        }
        if(cnt == 0)    break;
        rep(i,0,NV) {
            if(ID[i] == -1) ID[i] = cnt++;
        }
        rep(i,0,NE) {
            v = E_copy[i].v;
            E_copy[i].u = ID[E_copy[i].u];
            E_copy[i].v = ID[E_copy[i].v];
            if(E_copy[i].u != E_copy[i].v) {
                E_copy[i].cost -= In[v];
            }
        }
        NV = cnt;
        root = ID[root];
    }
    return ret;
}
}

int adj[105][105];
int main() {
	rep(it,0,100000) {
		bumpalloc.reset();
		int n = (rand()%100)+1;
		int r = rand()%n;
		int cnt = 0;
		DMST dmst(n);
		rep(i,0,n)
			rep(j,0,n){
				if (i==j) continue;
				int weight = rand()%100;
				mit::E[cnt++] = {i,j, weight};
				dmst.addEdge(i,j,weight);
			}
		int ans1 = mit::Directed_MST(r, n, cnt);
		int ans2 = dmst.solve(r);
		assert(ans1 == ans2);
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}