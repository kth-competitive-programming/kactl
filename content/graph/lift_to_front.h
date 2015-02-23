/**
 * Author:
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: Lift-to-front algorithm is a variant of
 * preflow-push algorithm.
 * Time: $O(V^3)$, where $V$ is the number of vertices. Possibly slow in practice.
 * Status: Works, tested on kattis maxflow
 */

typedef ll Flow;
struct Edge {
	int dest, back;
	Flow f, c;
};
typedef vector<vector<Edge> > graph;

void add_edge(graph& g, int s, int t, Flow cap, Flow rcap=0) {
	if (s == t) return;
	Edge a = {t, sz(g[t]), 0, cap};
	Edge b = {s, sz(g[s]), 0, rcap};
	g[s].push_back(a);
	g[t].push_back(b);
}

void add_flow(graph& g, Edge& e, Flow f, vector<Flow>& exc) {
	Edge &back = g[e.dest][e.back];
	e.f += f; e.c -= f; exc[e.dest] += f;
	back.f -= f; back.c += f; exc[back.dest] -= f;
}
Flow lift_to_front(graph& g, int s, int t) {
	int v = sz(g);
	vi l(v), hgt(v); // l == list, hgt == height
	vector<Flow> exc(v); // exc == excess
	vector<Edge*> cur(v);

	hgt[s] = v - 2;
	trav(e, g[s])
		add_flow(g, e, e.c, exc);
	int p = t; // make l a linked list from p to t (sink)
	rep(i,0,v) {
		if (i != s && i != t) l[i] = p, p = i;
		else l[i] = t;
		cur[i] = g[i].data();
	}

	int r = 0, u = p; // lift-to-front loop
	while (u != t) {
		int oldheight = hgt[u];
		while (exc[u] > 0)  // discharge u
			if (cur[u] == g[u].data() + sz(g[u])) {
				hgt[u] = 2 * v - 1; // lift u, find admissible edge
				trav(e, g[u]) if (e.c > 0 && hgt[e.dest] + 1 < hgt[u])
					hgt[u] = hgt[e.dest]+1, cur[u] = &e;
			} else if (cur[u]->c>0 && hgt[u]==hgt[cur[u]->dest]+1)
				add_flow(g, *cur[u], min(exc[u], cur[u]->c), exc);
			else ++cur[u];
		if (hgt[u] > oldheight && p != u)    // lift-to-front!
			l[r] = l[u], l[u] = p, p = u;      // u to front of list
		r = u, u = l[r];
	}
	return exc[t];
}
