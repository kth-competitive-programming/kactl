/**
 * Author: Marcus?
 * Date:
 * Source: tinyKACTL, Introduction to Algorithms
 * Description:
 */
#pragma once
#include <vector>

struct union_find {
  struct elem {
    int head, rank; // rank is a pseudo-height with height <= rank
    elem(int head) : head(head), rank(0) {}
  };

  vector<elem> e;

  union_find(int n) {
    for(int i = 0; i < n; i++) e.push_back(i);
  }

  int find(int x) { // Find set-head with path-compression
    if (x == e[x].head) return e[x].head;
    return e[x].head = find(e[x].head);
  }

  bool equal(int a, int b){ return (find(a)==find(b));}

  void join(int a, int b) { // union sets
    a = find(a); b = find(b);
    if(e[a].rank > e[b].rank) e[b].head = a;
    else {
      e[a].head = b;
      if(e[a].rank == e[b].rank) e[b].rank++;
    }
  }
};
