/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: N/A
 * Description: Find a maximum matching in a bipartite graph.
 * Status: Working
 * Usage: vi ba(m, -1); hopcroftKarp(g, ba);
 * Time: O(\sqrt{N}M)
 */

bool hopcroftKarp_dfs(int a,
				 int layer,
				 const vector<vector<int> >& AtoB,
				 vector<int>& BtoA,
				 vector<int>& layerA,
				 vector<int>& layerB)
{
	if(layerA[a] != layer)
		return false;

	layerA[a] = -1;
	int layerNextB = layer + 1, layerNextA = layer + 2;

	for(int i = 0; i < (int)AtoB[a].size(); ++i)
	{
		int b = AtoB[a][i];
		if(layerB[b] != layerNextB) continue;

		layerB[b] = -1;

		if(BtoA[b] == -1 || hopcroftKarp_dfs(BtoA[b], layerNextA, AtoB, BtoA, layerA, layerB))
		{
			BtoA[b] = a;
			return true;
		}
	}
	return false;
}

int hopcroftKarp(const vector<vector<int> >& AtoB,
			  vector<int>& BtoA)
{
	int incrMatching = 0;
	vector<int> layerA, layerB, bfsA, bfsANext;

	layerA.resize(AtoB.size());
	layerB.resize(BtoA.size());
	bfsA.resize(AtoB.size());
	bfsANext.resize(AtoB.size());

	int bfsAEnd;
	int bfsANextEnd;

	while(true) {
		fill(layerA.begin(), layerA.end(), 0);
		fill(layerB.begin(), layerB.end(), -1);

		// Find the starting nodes for BFS (i.e. layer 0).
		for(int b = 0; b < (int)BtoA.size(); ++b) {
			if(BtoA[b] != -1)
				layerA[BtoA[b]] = -1;
		}

		bfsAEnd = 0;
		for(int a = 0; a < (int)AtoB.size(); ++a) {
			if(layerA[a] == 0)
				bfsA[bfsAEnd++] = a;
		}

		// Find all layers using bfs.
		for(int layerNext = 1;; ++layerNext) {
			bool layerIsLast = false;

			bfsANextEnd = 0;
			for(int bfsAPos = 0; bfsAPos < bfsAEnd; ++bfsAPos) {
				int a = bfsA[bfsAPos];

				for(int i = 0; i < (int)AtoB[a].size(); ++i) {
					int b = AtoB[a][i];
					if(BtoA[b] == -1) {
						layerB[b] = layerNext;
						layerIsLast = true;
					}
					else if(BtoA[b] != a && layerB[b] == -1) {
						layerB[b] = layerNext;
						bfsANext[bfsANextEnd++] = BtoA[b];
					}
				}
			}

			if(layerIsLast) break;
			if(bfsANextEnd == 0) return incrMatching;
			++layerNext;

			for(int bfsANextPos = 0; bfsANextPos < bfsANextEnd; ++bfsANextPos) {
				int a = bfsANext[bfsANextPos];
				layerA[a] = layerNext;
			}

			bfsAEnd = bfsANextEnd;
			bfsA.swap(bfsANext);
		}

		// Use DFS to scan for augmenting paths.
		for(int a = 0; a < (int)AtoB.size(); ++a) {
			if(hopcroftKarp_dfs(a, 0, AtoB, BtoA, layerA, layerB))
				++incrMatching;
		}
	}
}
