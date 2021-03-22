import java.util.ArrayList;
import java.util.List;

/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Heavy Light Decomposition on multiple trees.
 */
class MultiTreeHeavyLightDecomposition {
  int n;
  Vertex[] g;

  class HLD {
    MaxSparseTable[] trees;
    List<List<Integer>> treeIndexes;
    int[] treeIndex;
    int[] indexInTree;

    HLD(List<Integer> roots) {
      treeIndex = new int[n];
      indexInTree = new int[n];
      treeIndexes = new ArrayList<>();
      for (int v : roots) {
        treeIndex[v] = treeIndexes.size();
        treeIndexes.add(new ArrayList<>());
        initIndexes(v);
      }
      initTables();
    }

    HLD() { this(findRoots()); }

    int getMax(int v, int u) {
      if (g[u].component != g[v].component) return -1;
      int max = -1;
      while (treeIndex[v] != treeIndex[u]) {
        if (g[head(v)].depth < g[head(u)].depth) {
          int t = v;
          v = u;
          u = t;
        }
        max = max(max,
                  trees[treeIndex[v]].get(0, indexInTree[v]));
        v = g[head(v)].parent;
      }
      if (v == u) return max;
      int l = min(indexInTree[v], indexInTree[u]) + 1;
      int r = max(indexInTree[v], indexInTree[u]);
      return max(max, trees[treeIndex[v]].get(l, r));
    }

    int head(int v) {
      return treeIndexes.get(treeIndex[v]).get(0);
    }

    void initTables() {
      int treeCount = treeIndexes.size();
      trees = new MaxSparseTable[treeCount];
      for (int i = 0; i < treeCount; i++) {
        int[] a = new int[treeIndexes.get(i).size()];
        for (int j = 0; j < a.length; j++)
          a[j] = g[treeIndexes.get(i).get(j)].inEdgeTime;
        trees[i] = new MaxSparseTable(a);
      }
    }

    void initIndexes(int v) {
      indexInTree[v] = treeIndexes.get(treeIndex[v]).size();
      treeIndexes.get(treeIndex[v]).add(v);
      for (Edge e : g[v].adj) {
        if (g[e.to].size > g[v].size / 2) {
          treeIndex[e.to] = treeIndex[v];
        } else {
          treeIndex[e.to] = treeIndexes.size();
          treeIndexes.add(new ArrayList<>());
        }
        initIndexes(e.to);
      }
    }
  }

  class Vertex {
    int index;
    List<Edge> adj = new ArrayList<>();
    int size;
    int inEdgeTime;
    int depth;
    int parent = -1;
    int component;

    Vertex(int index) {
      this.index = index;
    }

    void dfs() {
      size = 1;
      for (int i = 0; i < adj.size(); i++) {
        Edge e = adj.get(i);
        int to = e.to;
        if (to == parent) {
            adj.remove(i--);
            continue;
        }
        g[to].depth = depth + 1;
        g[to].parent = index;
        g[to].inEdgeTime = e.time;
        g[to].component = component;
        g[to].dfs();
        size += g[to].size;
      }
    }
  }

  List<Integer> findRoots() {
    List<Integer> roots = new ArrayList<>();
    for (Vertex v : g) {
      if (v.parent == -1) {
        v.component = roots.size();
        roots.add(v.index);
        g[v.index].dfs();
      }
    }
    return roots;
  }

  class Edge { int from, to, time; }
}
