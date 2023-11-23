/**
 * Author:
 * Description: Every variable x is encoded to 2i, $!x$ is 2i+1. n of TwoSAT means number of variables.
 * Usage:
 * TwoSat g(number of vars);
 * g.addCNF(x, y); // x or y
 * g.atMostOne({ a, b, ... });
 * auto ret = g.solve(void); if impossible empty
 * Time: O(V+E), note that sort in atMostOne function. $10^5$ simple cnf clauses 56ms.
 * Status: stress-tested
 */
#pragma once

struct TwoSAT {
    struct SCC {
        int n;
        vector<bool> chk;
        vector<vector<int>> E, F;
        SCC() {}
        
        void dfs(int x, vector<vector<int>> &E, vector<int> &st) {
            if(chk[x]) return;
            chk[x] = true;
            for(auto i : E[x]) dfs(i, E, st);
            st.push_back(x);
        }

        void init(vector<vector<int>> &E) {
            n = E.size();
            this->E = E;
            F.resize(n);
            chk.resize(n, false);
            for(int i = 0; i < n; i++)
                for(auto j : E[i]) F[j].push_back(i);
        }
        
        vector<vector<int>> getSCC() {
            vector<int> st;
            fill(chk.begin(), chk.end(), false);
            for(int i = 0; i < n; i++) dfs(i, E, st);
            reverse(st.begin(), st.end());
            fill(chk.begin(), chk.end(), false);
            vector<vector<int>> scc;
            for(int i = 0; i < n; i++) {
                if(chk[st[i]]) continue;
                vector<int> T;
                dfs(st[i], F, T);
                scc.push_back(T);
            }
            return scc;
        }
    };

    int n;
    vector<vector<int>> adj;
    TwoSAT(int n): n(n) {
        adj.resize(2*n);
    }

    int new_node() {
        adj.push_back(vector<int>());
        adj.push_back(vector<int>());
        return n++;
    }
    
    void add_edge(int a, int b) {
        adj[a].push_back(b);
    }

    void add_cnf(int a, int b) {
        add_edge(a^1, b);
        add_edge(b^1, a);
    }

    // arr elements need to be unique
    // Add n dummy variable, 3n-2 edges
    // yi = x1 | x2 | ... | xi, xi->yi, yi->y(i+1), yi->!x(i+1)
    void at_most_one(vector<int> arr) {
        sort(arr.begin(), arr.end());
        assert(unique(arr.begin(), arr.end()) == arr.end());
        for (int i=0; i<arr.size(); ++i) {
            int now = new_node();
            add_cnf(arr[i]^1, 2*now);
            if (i == 0) continue;
            add_cnf(2*(now-1)+1, 2*now);
            add_cnf(2*(now-1)+1, arr[i]^1);
        }
    }

    vector<int> solve() {
        SCC g;
        g.init(adj);
        auto scc = g.getSCC();
        
        vector<int> rev(2*n, -1);
        for (int i=0; i<scc.size(); ++i) {
            for (int x: scc[i]) rev[x] = i;
        }
        for (int i=0; i<n; ++i) {
            if (rev[2*i] == rev[2*i+1]) return vector<int>();
        }
        
        vector<int> ret(n);
        for (int i=0; i<n; ++i) ret[i] = (rev[2*i] > rev[2*i+1]);
        return ret;
    }
};
