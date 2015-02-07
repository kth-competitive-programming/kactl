/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * Source: Folklore
 * Status: Tested at Petrozavodsk
 * Description: Calculate power of two jumps
 * in a tree.
 * Time: $O(|V| \log |V|)$
 */

vector<vi> treeJump(vi& P){
	int on = 1, depth = 1;
	while(on < (int)P.size()) on *= 2, depth++;
	vector<vi> jmp;
	jmp.assign(depth, vi(P.size()));
	jmp[0] = P;
	rep(i,1,depth) rep(j,0,P.size())
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}


