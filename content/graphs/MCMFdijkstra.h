/**
 * Author: Tyler M
 * Date: 2024-02-02
 * Source: various cf blogs
 * Description: If SPFA TLEs, swap the find\_path function in MCMF
 * 	with the one below and in\_q with seen. If negative edge weights 
 * 	can occur, initialize pi with the shortest path from the source 
 * 	to each node using Bellman-Ford. Negative weight cycles not 
 * 	supported.
 */
#pragma once

bool find_path(int s, int t) {
	fill(all(dist), inf);
	fill(all(seen), 0);
	dist[s] = 0;
	__gnu_pbds::priority_queue<pair<ll, int>> pq;
	vector<decltype(pq)::point_iterator> its(n);
	pq.push({0, s});
	while(!pq.empty()) {
		auto [d, cur] = pq.top(); pq.pop(); d *= -1;
		seen[cur] = 1;
		if(dist[cur] < d) continue;
		for(int idx: adj[cur]) {
			auto [nxt, cap, f, wt] = edges[idx];
			ll nxtD = d + wt + pi[cur] - pi[nxt];
			if(f >= cap || nxtD >= dist[nxt] || seen[nxt]) continue;
			dist[nxt] = nxtD;
			par[nxt] = {cur, idx};
			if(its[nxt] == pq.end()) its[nxt] = pq.push({-nxtD, nxt});
			else pq.modify(its[nxt], {-nxtD, nxt});
		}
	}
	rep(i, 0, n) pi[i] = min(pi[i] + dist[i], inf);
	return seen[t];
}