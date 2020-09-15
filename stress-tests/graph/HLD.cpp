#include "../utilities/template.h"
#include "../utilities/genTree.h"

#include "../../content/graph/HLD.h"

namespace old {
#include "oldHLD.h"
}
struct bruteforce { // values in nodes
    vector<vector<int>> tree;
    vector<int> vals;
    vector<int> pars;
    int unit = -1e9;
    int f(int a, int b) { return max(a, b); }
    void root(int cur, int p = -1) {
        pars[cur] = p;
        for (auto i: tree[cur]) {
            if (i != p) root(i, cur);
        }
    }
    bruteforce(vector<vector<int>> _tree): tree(_tree), vals(sz(tree)), pars(sz(tree)) {
        root(0);
    }
    bool dfsModify(int cur, int target, int val, int p=-1) {
        if (cur == target) {
            vals[cur] += val;
            return true;
        }
        bool alongPath = false;
        for (auto i: tree[cur]) {
            if (i == p) continue;
            alongPath |= dfsModify(i, target, val, cur);
        }
        if (alongPath) vals[cur] += val;
        return alongPath;
    }
    void modifyPath(int a, int b, int val) {
        dfsModify(a, b, val);
    }

    int dfsQuery(int cur, int target, int p = -1) {
        if (cur == target) {
            return vals[cur];
        }
        int res = unit;
        for (auto i: tree[cur]) {
            if (i == p) continue;
            res = f(res, dfsQuery(i, target, cur));
        }
        if (res != unit) {
            return f(res, vals[cur]);
        }
        return res;
    }
    int queryPath(int a, int b) {
        return dfsQuery(a, b);
    }
    int dfsSubtree(int cur, int p) {
        int res = vals[cur];
        for (auto i: tree[cur]) {
            if (i != p)
                res = f(res, dfsSubtree(i, cur));
        }
        return res;
    }
    int querySubtree(int a) {
        return dfsSubtree(a, pars[a]);
    }
};

void testAgainstOld(int n, int iters, int queries) {
    for (int trees = 0; trees < iters; trees++) {
        auto graph = genRandomTree(n);
        vector<vector<int>> tree1(n);
        vector<vector<pair<int, int>>> tree2(n);
        for (auto i : graph) {
            tree1[i.first].push_back(i.second);
            tree1[i.second].push_back(i.first);
        }
        for (int i = 0; i < sz(tree1); i++) {
            for (auto j : tree1[i]) {
                tree2[i].push_back({j, 0});
            }
        }
        HLD<false> hld(tree1);
        old::HLD hld2(tree2);
        hld.tree->set(0, n, 0);
        for (int itr = 0; itr < queries; itr++) {
            if (rand() % 2) {
                int node = rand() % n;
                int val = rand() % 10;
                hld2.update(node, val);
                hld.modifyPath(node, node, val - hld.queryPath(node, node));
            } else {
                int a = rand() % n;
                int b = rand() % n;
                assert(hld.queryPath(a, b) == hld2.query2(a, b).first);
            }
        }
    }
}
void testAgainstBrute(int n, int iters, int queries) {
    for (int trees = 0; trees < iters; trees++) {
        auto graph = genRandomTree(n);
        vector<vector<int>> tree1(n);
        for (auto i : graph) {
            tree1[i.first].push_back(i.second);
            tree1[i.second].push_back(i.first);
        }
        HLD<false> hld(tree1);
        bruteforce hld2(tree1);
        hld.tree->set(0, n, 0);
        for (int itr = 0; itr < queries; itr++) {
            int rng = rand() % 3;
            if (rng == 0) {
                int a = rand() % n;
                int b = rand() % n;
                int val = rand() % 10;
                hld.modifyPath(a, b, val);
                hld2.modifyPath(a, b, val);
            } else if (rng == 1){
                int a = rand() % n;
                int b = rand() % n;
                hld.queryPath(a, b);
                hld2.queryPath(a, b);
                assert(hld.queryPath(a, b) == hld2.queryPath(a, b));
            } else if (rng == 2) {
                int a = rand() % n;
                assert(hld.querySubtree(a) == hld2.querySubtree(a));
            }
        }
    }

}
int main() {
    srand(2);
    testAgainstBrute(5, 1000, 10000);
    testAgainstBrute(1000, 100, 100);
    testAgainstOld(5, 1000, 100);
    testAgainstOld(10000, 100, 1000);
    cout<<"Tests passed!"<<endl;
    return 0;
}
