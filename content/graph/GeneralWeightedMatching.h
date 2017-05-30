/**
 * Author: Unknown
 * Date: Unknown
 * Source: tinyKACTL
 * Description: General weighted matching.
 * Time: O(N^3)
 * Status: untested
 */
#pragma once

/// TODO:
/// fix brokenness that Austrin mentioned
/// clean up unpair_all
/// clean away secondmate
/// try to understand the code better
typedef int Weight;
template <int maxV=50, int maxE=500, int asize = maxV+2*maxE+3>
struct matcher {
	int V, dummyVtx, dummyEdge;
	Weight weight[asize], y[maxV+2], nextd[maxV+2], lastd, delta;
	int a[asize], end[asize], nextpair[asize];
	int mate[maxV+2], link[maxV+2], base[maxV+2];
	int nextvtx[maxV+2], lastvtx[maxV+2], nextedge[maxV+2];
	int lastedge[2], secondmate;

	template <class AdjList> // NB!! 1-indexed vertices!!
	int max_match(AdjList *graph, int _V) {
		typedef typename AdjList::iterator It;
		int E = (V = _V) | 1, v;
		memset(a, 0, sizeof(a));
		memset(lastedge, 0, sizeof(lastedge));
		memset(nextpair, 0, sizeof(nextpair));
		memset(nextvtx, 0, sizeof(nextvtx));
		lastd = secondmate = 0;
		for (int i = 1; i <= V; ++i) // init
			for (It it = graph[i].begin(); it != graph[i].end(); ++it)
				if (it->first > i) {
					E += 2;
					lastd = max(lastd, weight[E] = 4*it->second);
					end[E-1] = i;
					end[E] = it->first;
					/// Isn't "a" just a linked list of the edges leading out of
					/// a vertex, ordered by destination vertex??? Can it be
					/// replaced by the actual adjacency list (possibly if we
					/// sort the edges by vertex numbers first??)
					for (v = i; a[v] && end[a[v]] <= it->first; v = a[v]);
					a[E] = a[v];
					a[v] = E;
					for (v = it->first; a[v]; v = a[v]);
					a[v] = E-1;
				}
		dummyVtx = V+1;
		dummyEdge = E+1;
		end[dummyEdge] = dummyVtx;
		lastd /= 2;
		for (int i = 1; i <= V+1; ++i) { // more init...
			mate[i] = nextedge[i] = dummyEdge;
			link[i] = -dummyEdge;
			base[i] = lastvtx[i] = i;
			y[i] = nextd[i] = lastd;
		}

		for (int e, loop=1;; ++loop) { // solve!
			delta = 0;
			for (v = 1; v <= V; ++v)
				if (mate[v] == dummyEdge)
					pointer(dummyVtx, v, dummyEdge);
			for (e = 0; !e; ) {
				v = min_element(nextd+1, nextd+V+1) - nextd;
				if ((delta = nextd[v]) == lastd) goto done;

				int ne = nextedge[v];
				v = base[v];
				if (link[v] < 0) {
					int w = bmate(v);
					if (link[w] < 0) pointer(v, w, oppedge(ne));
					else unpair(v, w);
				} else e = pair(v);
			}

			lastd -= delta;
			set_bounds();
			rematch(bend(e), oppedge(e));
			rematch(bend(oppedge(e)), e);
		}
		done: // postprocess
		set_bounds();
		unpair_all();
		int ans = 0;
		for (int i = 1; i <= V; ++i)
			if (end[mate[i]] == dummyVtx) mate[i] = 0;
			else ans += weight[mate[i]|1], mate[i] = end[mate[i]];
		return ans / 8;
	}
	// Assign a pointer link to a vertex. Edge e joins a vertex
	// in blossom u to a linked vertex.
	void pointer(int u, int v, int e) {
		int i;
		Weight del;
		link[u] = -dummyEdge;
		nextbase(u) = nextbase(v) = dummyVtx;
		del = (lastvtx[u] == u) ? lastd : -slack(mate[nextvtx[u]])/2;
		for (int i = u; i != dummyVtx; i = nextvtx[i])
			y[i] += del, nextd[i] += del;
		if (link[v] < 0) {
			link[v] = e;
			nextpair[dummyEdge] = dummyEdge;
			scan(v, delta);
		}
		link[v] = e;
	}
	// Scan each vertex in the blossom whose base is x
	int scan(int x, Weight del) {
		int newbase = base[x], stopscan = nextbase(x);
		for ( ; x != stopscan; x = nextvtx[x]) {
			int pairpt = dummyEdge, u;
			y[x] += del;
			nextd[x] = lastd;
			for (int e = a[x]; e; e = a[e])
				if (link[u = bend(e)] < 0) {
					if ((link[bmate(u)] < 0 || lastvtx[u] != u) &&
							nextd[end[e]] > slack(e))
						nextd[end[e]] = slack(e), nextedge[end[e]] = e;
				} else if (u != newbase) insert_pair(newbase, e, pairpt);
		}
		nextedge[newbase] = nextpair[dummyEdge];
		return newbase;
	}

	// Process an edge linking two linked vertices,
	// v is the base of one end of the linking edge.
	// Returns edge on success
	int pair(int v) {
		int e = nextedge[v];
		while (slack(e) != 2*delta) e = nextpair[e];
		int w = bend(e), u = bmate(v);
		for (link[bmate(w)] = -e; link[u] != -e;
				v = base[end[link[v]]], u = bmate(v)) {
			link[u] = -e;
			if (mate[w] != dummyEdge) swap(v, w);
		}
		if (u == dummyVtx && v != w) return e;
		int newlast = v, oldfirst = nextvtx[v], i;
		link_path(v, e, newlast);
		link_path(v, oppedge(e), newlast);
		nextvtx[newlast] = oldfirst;
		if (lastvtx[v] == v) lastvtx[v] = newlast;
		nextpair[dummyEdge] = dummyEdge;
		merge_pairs(v, v);
		i = nextvtx[v];
		do {
			merge_pairs(v, i);
			i = nextbase(i);
			v = scan(i, 2*delta - slack(mate[i]));
			i = nextbase(i);
		} while (i != oldfirst);
		return 0;
	}

	// Merge a subblossom's pair list into a new blossom's pair list
	// v is the base of the previously unlinked subblossom
	// b is the base of the new blossom
	// nextpair[dummyEdge] is the first edge on b's pair list
	void merge_pairs(int b, int v) {
		int pairpt = dummyEdge, e = nextedge[v], ne = nextpair[e];
		nextd[v] = lastd;
		for ( ; e != dummyEdge; e = ne, ne = nextpair[e])
			if (bend(e) != b) insert_pair(b, e, pairpt);
	}

	// links the unlinked vertices in the path P(end[v], b)
	// b is the base vertex of the new blossom
	// newlast is the last vertex in b's current blossom
	void link_path(int b, int e, int &newlast) {
		for (int v = bend(e); v != b; e = link[v], v = bend(e)) {
			int u = bmate(v);
			link[u] = oppedge(e);
			nextvtx[newlast] = v;
			nextbase(v) = u;
			newlast = lastvtx[u];
			for (int i=v; i != dummyVtx; base[i] = b, i = nextvtx[i]);
		}
	}

	// update a blossom's pair list.
	// e is the edge to be inserted.
	// pairpoint is the next pair on the pair list
	void insert_pair(int b, int e, int &pairpoint) {
		int nextpoint = nextpair[pairpoint];
		while (end[nextpoint] < end[e])
			nextpoint = nextpair[pairpoint = nextpoint];
		if (end[nextpoint] == end[e]) {
			if (slack(e) >= slack(nextpoint)) return;
			nextpoint = nextpair[nextpoint];
		}
		nextpair[pairpoint] = e;
		nextpair[pairpoint = e] = nextpoint;
		nextd[b] = min(nextd[b], slack(e)/2);
	}

	// expands a blossom. fixes up link and mate
	void unpair(int oldbase, int oldmate) {
		int e, newbase, u;
		unlink(oldbase);
		newbase = bmate(oldmate);
		if (newbase != oldbase) {
			link[oldbase] = -dummyEdge;
			if (rematch(newbase, mate[oldbase]) == lastedge[0])
				link[secondmate] = -lastedge[1]; // NB! rematch affects
			else link[secondmate] = -lastedge[0]; // secondmate!
		}
		u = bend(oppedge(e = link[oldmate]));
		if (u != newbase) {
			link[bmate(u)] = -e;
			for ( ; u != newbase; u = bend(e))
				e = -link[u], pointer(u, bmate(u), -link[bmate(u)]);
			e = oppedge(e);
		}
		pointer(newbase, oldmate, e);
	}

	// changes the matching along an alternating path
	// firstmate is the first base vertex on the path
	// edge e is the new matched edge for firstmate
	int rematch(int firstmate, int e) {
		mate[firstmate] = e;
		int eopp = 0;
		for (int ne = -link[firstmate]; ne != dummyEdge ; ) {
			firstmate = bend(e = ne);
			secondmate = bend(eopp = oppedge(e));
			ne = -link[firstmate];
			link[firstmate] = -mate[secondmate];
			link[secondmate] = -mate[firstmate];
			mate[firstmate] = eopp;
			mate[secondmate] = e;
		}
		return eopp;
	}

	// unlinks subblossoms in a blossom. oldbase is the base of
	// the blossom to be unlinked
	int unlink(int oldbase) {
		int i = nextvtx[oldbase], newbase = i;
		int e = link[nextbase(i)];
		for (int j = 0; j < 2; ++j) {
			do {
				lastedge[j] = oppedge(link[newbase]);
				for (int k = 0; k < 2; ++k) {
					link[newbase] = -link[newbase];
					do base[i] = newbase, i = nextvtx[i];
					while (i != nextbase(newbase));
					newbase = nextbase(newbase);
				}
			} while (link[nextbase(newbase)] == lastedge[j]);
			if (!j && link[nextbase(newbase)] != oppedge(e)) {
				lastedge[1] = lastedge[0];
				break;
			}
		}
		if (base[lastvtx[oldbase]] == oldbase)
			nextvtx[oldbase] = newbase;
		else nextvtx[lastvtx[oldbase] = oldbase] = dummyVtx;
		return e;
	}

	// updates numerical bounds for linking paths
	// called with lastd set to the bound on delta for next search
	void set_bounds() {
		for (int v = 1; v <= V; nextd[v] = lastd, ++v) {
			if (link[v] < 0 || base[v] != v) continue;
			link[v] = -link[v];
			for (int i=v; i != dummyVtx; y[i] -= delta, i=nextvtx[i]);
			int e = mate[v];
			Weight del = slack(e);
			if (e != dummyEdge)
				for(int i=bend(e); i!=dummyVtx; y[i]-=del, i=nextvtx[i]);
		}
	}
	// undoes all blossoms to get the final matching
	void unpair_all() {
		for (int v = 1; v <= V; ++v) {
			if (base[v] != v || lastvtx[v] == v) continue;
			int nextu = v;
			nextbase(nextu) = dummyVtx;
			do {
				int u = nextu;
				nextu = nextvtx[u];
				int e = unlink(u);
				if (lastvtx[u] != u)
					nextbase(bend((lastedge[1] == oppedge(e)) ?
								lastedge[0] : lastedge[1])) = u;
				int newbase = bmate(bmate(u));
				if (newbase != dummyVtx && newbase != u) {
					link[u] = -dummyEdge;
					rematch(newbase, mate[u]);
				}
				while (nextu == lastvtx[nextu] && nextu != dummyVtx)
					nextu = nextvtx[nextu];
			} while (lastvtx[nextu] != nextu);
		}
	}
	// utility functions
	int& nextbase(int v){ return nextvtx[lastvtx[v]]; }
	int bend(int e) { return base[end[e]]; }
	int bmate(int v) { return base[end[mate[v]]]; }
	int oppedge(int e) { return e ^ 1; }
	Weight slack(int e){
		return y[end[e]]+y[end[e^1]]-weight[e|1]; }
};
