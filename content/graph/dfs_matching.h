/**
 * Author: Lukas
 * Date: 2009-10-28
 * Source:
 * Description: This is a silly matching algorithm but should
 * be just fine in most cases. Graph $g$ should be a list of
 * neighbours of the left partition. $n$ is the size of the left
 * partition and $m$ is the size of the right partition.
 * If you want to get the matched pairs, $match[i]$ contains
 * match for vertex $i$ on the right side or $-1$ if it's not
 * matched.
 * Time: $O(NM)$
 * Status: works
 */
#include <algorithm>
#include <vector>
using namespace std;

vector<int> match;
vector<bool> seen;
template<class G>
bool find(int j, G &g) {
	typedef typename G::value_type::const_iterator E_iter;
	if (match[j] == -1) return true;
	seen[j] = true; int di = match[j];
	for (E_iter e = g[di].begin(); e != g[di].end(); e++)
		if (!seen[*e] && find(*e, g)) {
			match[*e] = di;
			match[j] = -1;
			return true;
		}
	return false;
}
template<class G>
int dfs_matching(G &g, int n, int m) {
	typedef typename G::value_type::const_iterator E_iter;
	match.assign(m, -1);
	rep(i,0,n) {
		seen.assign(m, false);
		rep(j,0,g[i].size())
			if (find(g[i][j], g)) {
				match[g[i][j]] = i;
				break;
			}
	}
	return m - count(match.begin(), match.end(), -1);
}
