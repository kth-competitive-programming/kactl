/**
 * Author: 
 * Description: link-cut Tree.
 */
struct LinkCut {
  struct Node {
    bool flip = 0;
    Node *pp, *p, *c[2];
    // add stuff
  };

  vector<Node> node;
  vector<Node*> f;
  Node *null;
	LinkCut(int N) : node(N), f(N), null(new Node) {
    null -> c[0] = null -> c[1] = null -> p = null -> pp = null;
    rep(i, 0, N) {
      f[i] = &node[i];
      f[i] -> c[0] = f[i] -> c[1] = f[i] -> p = f[i] -> pp = null;
    }
  }

  void push(Node *x) {
    if (x -> flip) {
      x -> c[0] -> flip ^= 1;
      x -> c[1] -> flip ^= 1;
      swap(x -> c[0], x -> c[1]);
      x -> flip = false;
    }
    // add stuff
  }

  void pull(Node *x) {
    push(x -> c[0]);
    push(x -> c[1]);
    // add stuff
  }

  void rot(Node *x, bool t) { /// start-hash
    Node *y = x -> p, *z = y -> p;
    if (z != null)  z -> c[z -> c[1] == y] = x;
    x -> p = z;
    y -> c[t] = x -> c[!t];
    x -> c[!t] -> p = y;
    x -> c[!t] = y;
    y -> p = x;
    pull(z);
    pull(y);
  } /// end-hash

  void xiao(Node *x) {
    if (x -> p != null)  xiao(x -> p), x -> pp = x -> p -> pp;
    push(x);
  }

  void splay(Node *x) { /// start-hash
    xiao(x);
    Node *y, *z;
    while (x -> p != null) {
      y = x -> p; z = y -> p;
      bool t1 = (y -> c[1] == x), t2 = (z -> c[1] == y);
      if (z != null) {
        if (t1 == t2) rot(y, t2), rot(x, t1);
        else  rot(x, t1), rot(x, t2);
      } else rot(x, t1);
    }
    pull(x);
  } /// end-hash

  Node* access(Node *x) {/// start-hash
    for (Node *y = null, *z = x; z != null; y = z, z = z -> pp) {
        splay(z);
        z -> c[1] -> pp = z;
        z -> c[1] -> p = null;
        z -> c[1] = y;
        y -> p = z;
        push(z);
    }
    splay(x);
    x -> flip = true;
		push(x);
    return x;
  } /// end-hash

  bool cut(int u, int v) { /// start-hash
    access(f[u]);
    access(f[v]);
    if (f[v] -> c[1] != f[u] || f[u] -> c[0] != null)
      return false;
    f[v] -> c[1] = null;
    f[u] -> p = f[u] -> pp = null;
    pull(f[u]);
    pull(f[v]);
    return true;
  } /// end-hash

  bool isConnected(int u, int v) {
    access(f[u]);
    access(f[v]);
    return f[u] == f[v] || f[u] -> p != null;
  }

  bool link(int u, int v) {
    if (isConnected(u, v))
      return false;
    access(f[u]);
    access(f[v]);
    f[u] -> pp = f[v];
    return true;
  }
};