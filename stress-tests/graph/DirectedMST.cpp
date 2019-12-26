#include "../utilities/template.h"

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
	rep(it,0,50000) {
		bumpalloc.reset();
		int n = (rand()%20)+1;
		int density = rand() % 101;
		int r = rand()%n;
		int cnt = 0;
		vector<Edge> edges;
		rep(i,0,n)
			rep(j,0,n){
				if (i==j) continue;
				if (rand() % 100 >= density) continue;
				int weight = rand()%100;
				mit::E[cnt++] = {i,j, weight};
				edges.push_back({i,j,weight});
				adj[i][j] = weight;
			}

		ll ans1 = mit::Directed_MST(r, n, cnt);
		auto pa = dmst(n, r, edges);
		ll ans2 = pa.first;
		assert(ans1 == ans2);

		// Verifying reconstruction:
		if (ans1 != -1) {
			vi par = pa.second;
			if (0) {
				cout << "r = " << r << endl;
				for(auto &x: par) cout << x << ' ';
				cout << endl;
				for(auto &e: edges) {
					cout << e.a << ' ' << e.b << ' ' << e.w << endl;
				}
			}
			ll sum = 0;
			vector<vi> ch(n);
			rep(i,0,n) {
				if (i == r) assert(par[i] == -1);
				else {
					assert(par[i] != -1);
					sum += adj[par[i]][i];
					ch[par[i]].push_back(i);
				}
			}
			assert(sum == ans1);
			vi seen(n), q = {r};
			rep(qi,0,sz(q)) {
				int s = q[qi];
				if (!seen[s]++)
					for(auto &x: ch[s]) q.push_back(x);
			}
			assert(count(all(seen), 0) == 0);
		}
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
