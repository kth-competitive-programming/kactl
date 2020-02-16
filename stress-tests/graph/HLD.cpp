#include "../utilities/template.h"
#include "../utilities/genTree.h"

#include "../../content/graph/HLD.h"

namespace old {
#include "oldHLD.h"
}

void testAgainstOld(int n, int iters, int queries) {
    for (int trees = 0; trees < iters; trees++) {
        auto graph = genRandomTree(n);
        vector<vector<int>> tree1(n);
        vector<vector<pair<int, int>>> tree2(n);
        for (auto i : graph) {
            tree1[i.first].push_back(i.second);
            tree1[i.second].push_back(i.first);
        }
        for (int i = 0; i < tree1.size(); i++) {
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
int main() {
    srand(2);
	testAgainstOld(5, 1000, 100);
	testAgainstOld(10000, 100, 1000);
	cout<<"Tests passed!"<<endl;
    return 0;
}