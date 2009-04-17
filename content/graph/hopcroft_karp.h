/**
 * Author:
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: N/A
 * Status: Unknown
 */
#include <queue>
#include <utility>

template< class M >
bool hk_recurse(int b, int *lPred, vector<int> *rPreds, M m_b) {
  vector<int> L;
  L.swap(rPreds[b]);
  for(unsigned i = 0; i < L.size(); ++i) {
    int a = L[i], b2 = lPred[a];
    lPred[a] = -2;
    if(b2 == -2) continue;
    if(b2 == -1 || hk_recurse(b2, lPred, rPreds, m_b)) {
      m_b[b] = a;
      return true;
    }
  }
  return false;
}


template< class G, class M, class T >
int hopcroft_karp(G g, int n, int m, M match_b,
		  T mis_a, T mis_b) {
  typedef typename G::value_type::const_iterator E_iter;

  int lPred[n];
  vector<int> rPreds[m];
  queue<int> leftQ, rightQ, unmatchedQ;
  bool rProc[m], rNextProc[m];

  for(int i = 0; i < m; i++)
    match_b[i] = -1;

  // Greedy matching (start)
  for(int i = 0; i < n; i++)
    for(E_iter e = g[i].begin(); e != g[i].end(); ++e)
      if(match_b[*e] < 0) {
	match_b[*e] = i;
	break;
      }

  while(true) {
    for(int i = 0; i < n; ++i)
      lPred[i] = -1; // i is in the first layer
    for(int j = 0; j < m; ++j)
      if(match_b[j] >= 0)
	lPred[match_b[j]] = -2;//remove from layer alltogether
    for(int j = 0; j < m; ++j)
      rPreds[j].clear(), rProc[j] = rNextProc[j] = false;
    for(int i = 0; i < n; ++i)
      if(lPred[i] == -1) leftQ.push(i);

    while(!leftQ.empty() && unmatchedQ.empty()) {
      while(!leftQ.empty()) {
	int a = leftQ.front(); leftQ.pop();
	for(E_iter e = g[a].begin(); e != g[a].end(); ++e )
	  if(!rProc[*e]) {
	    rPreds[*e].push_back(a);
	    if(!rNextProc[*e])
	      rightQ.push(*e), rNextProc[*e] = true;
	  }
      }
      while(!rightQ.empty()) {
	int b = rightQ.front(); rightQ.pop();
	rProc[b] = true;
	if(match_b[b] >= 0)
	  leftQ.push(match_b[b]), lPred[match_b[b]] = b;
	else unmatchedQ.push( b );
      }
    }

    while(!leftQ.empty()) leftQ.pop();

    if(unmatchedQ.empty()) { // No more alternating paths
      int nMatch = 0;
      for(int i = 0; i < n; ++i)
	mis_a[i] = lPred[i]>=-1;
      for(int j = 0; j < m; ++j)
	mis_b[j] = !rProc[j], nMatch += match_b[j]>=0;
      return nMatch;
    }

    while(!unmatchedQ.empty()) {
      int b = unmatchedQ.front(); unmatchedQ.pop();
      hk_recurse( b, lPred, rPreds, match_b );
    }
  }
}
