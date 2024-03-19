/**
 * Author: Eu-Shaun Leong
 * Date: 2024-03-19
 * License: CC0
 * Source: me
 * Description: Mark a node and query "what is the shortest distance to a marked node X?"
 * Time: O(\log N)
 * Status: stress-tested on https://codebreaker.xyz/problem/factories
 */
#pragma once

struct CenDecomp {
	const ll INF=LLONG_MAX/3;
	const int LOGN=22;
	int N;
	vector<vector<pi>>adj;
	vi sze,ch,cp;
	vector<vector<ll>> dist;
	vector<ll> dp;

	int szdfs(int v, int par){
    	sze[v]=1;
		for(auto i:adj[v])if(cp[i.fst]==-2 && i.fst!=par) sze[v]+=szdfs(i.fst,v);
		return sze[v];
	}
	int cen(int v, int par, int n){
		for(auto i:adj[v])if(cp[i.fst]==-2 && i.fst!=par && sze[i.fst]>n/2)return cen(i.fst,v,n);
		return v;
	}
	void dfs(int v, int par, int h, ll d){
		dist[h][v]=d;
		for(auto i:adj[v])if(cp[i.fst]==-2 && i.fst!=par)dfs(i.fst,v,h,d+i.snd);
	}
	void decomp(int v, int par, int h){
		int c=cen(v,-1,szdfs(v,-1));
		dfs(c,-1,h,0);
		cp[c]=par;
		ch[c]=h;
		for(auto i:adj[c])if(cp[i.fst]==-2)decomp(i.fst,c,h+1);
	}
	CenDecomp(vector<vector<pi>>adj) : N(sz(adj)), adj(adj), sze(N), ch(N), cp(N,-2), dist(LOGN,vector<ll>(N)), dp(N,INF) { decomp(0,-1,0); }
	void update(int x) { for(int v=x;v!=-1;v=cp[v]) dp[v]=min(dp[v],dist[ch[v]][x]); }
	ll query(int x){
		ll res=LLONG_MAX;
		for(int v=x;v!=-1;v=cp[v])res=min(res,dp[v]+dist[ch[v]][x]);
		return res;
	}
};