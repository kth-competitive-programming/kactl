/**
 * Author: Lukas
 * Date: 2009-10-28
 * Source:
 * Description: This is a simple matching algorithm but should
 * be just fine in most cases. Graph $g$ should be a list of
 * neighbours of the left partition. $n$ is the size of the left
 * partition and $m$ is the size of the right partition.
 * If you want to get the matched pairs, $match[i]$ contains
 * match for vertex $i$ on the right side or $-1$ if it's not
 * matched.
 * Time: O(EV) where $E$ is the number of edges and V is the number of vertices.
 * Status: works
 */
#include <algorithm>
#include <vector>
using namespace std;

vector<int> match;
vector<bool> seen;
template<class G>
bool find(int j, G &g) {
	if (match[j] == -1) return true;
	seen[j] = true; int di = match[j];
	trav(e, g[di])
		if (!seen[*e] && find(*e, g)) {
			match[*e] = di;
			match[j] = -1;
			return true;
		}
	return false;
}
template<class G>
int dfs_matching(G &g, int n, int m) {
	match.assign(m, -1);
	rep(i,0,n) {
		seen.assign(m, false);
		trav(j,g[i])
			if (find(*j, g)) {
				match[*j] = i;
				break;
			}
	}
	return m - count(match.begin(), match.end(), -1);
}
