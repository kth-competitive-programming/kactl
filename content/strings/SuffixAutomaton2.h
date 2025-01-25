/**
 * Author: Sachin Sivakumar
 * Date: 2025-01-24
 * Description: Adds endpos (number of occurrences of substring),
 * to and from (number of paths to and from node), suffadj (reversed 
 * suffix link graph), topnext and toplink (topsort of nodes
 * by transition and suffix links).
 * Status: works but not stress tested
 */
#pragma once

int endpos; ll to, from = 1; // add to end of st
a[last].endpos++; // add to end of char loop
// add to Suffix Automaton
vi topnext, toplink; vvi suffadj;
// add to end of constructor
suffadj.resize(sz(a));
rep(u, 1, sz(a)) suffadj[a[u].link].push_back(u);
vi seen(sz(a));
auto dfs = [&](int u, auto &&dfs) {
	if(seen[u]) return;
	seen[u] = true;
	for(auto [c, v] : a[u].next)
		dfs(v, dfs), a[u].from += a[v].from;
	topnext.push_back(u);
};
dfs(0, dfs);
seen = vi(sz(a));
auto dfs1 = [&](int u, auto &&dfs1) {
	if(seen[u]) return;
	seen[u] = true;
	for(int v : suffadj[u]) dfs1(v, dfs1);
	toplink.push_back(u);
};
dfs1(0, dfs1);
rep(i, 0, sz(a)-1) 
	a[a[toplink[i]].link].endpos += a[toplink[i]].endpos;
reverse(all(topnext)), reverse(all(toplink));
a[0].to = 1;
for(int u : topnext)
	for(auto [c, v] : a[u].next)
		a[v].to += a[u].to;
