/**
 * Author: Lukas Polacek
 * Date: 2009-10-31
 * Source: marian's (TC) code
 * Description: Aho-Corasick tree is used for mutiple pattern
 * matching.
 * Usage: Initialize the tree with create(patterns) where no
 * string in patterns is a suffix of another string. It can be rewritten to
 * suffix-friendly version but I never needed this. So be careful when using
 * this. find(word) returns, for each position in word, -1 if no pattern ends
 * here or i if pattern[i] ends here.
 * Time: Function create is $O(N_1+\dots+N_k)$ where $N_i$ is the length of the
 * $i$-th. Function find is $O(M)$ where $M$ is the length of the word.
 * Status: tested
 */
#include <cstring>

struct Node {
	int back, next[26], ends;
	Node() { memset(next,0xff,sizeof(next)); ends = -1; }
};
vector<Node> nodes;
void insert(string &s, int j) {
	int n=0;
	for (int i = 0; i < s.size(); i++) {
		if (nodes[n].next[s[i]-'A'] == -1) {
			nodes[n].next[s[i]-'A'] = nodes.size();
			nodes.push_back(Node());
		}
		n = nodes[n].next[s[i]-'A'];
	}
	nodes[n].ends = j;
}
void create(vector<string> &s) {
	nodes.assign(1, Node());
	for (size_t i = 0; i < s.size(); i++) insert(s[i], i);
	nodes.push_back(Node());
	for (int i=0;i<26;i++) nodes.back().next[i]=0;
	nodes[0].back = nodes.size() - 1;

	queue<int> q;
	for (q.push(0); !q.empty(); q.pop()) {
		int n = q.front();
		for (int i = 0; i < 26; i++)
			if (nodes[n].next[i] == -1)
				nodes[n].next[i]=nodes[nodes[n].back].next[i];
			else {
				nodes[nodes[n].next[i]].back =
					nodes[nodes[n].back].next[i];
				q.push(nodes[n].next[i]);
			}
	}
}
vi find(string word) {
	int n = 0;
	vi res(word.size());
	for (int i = 0; i < word.size(); i++) {
		n = nodes[n].next[word[i]-'A'];
		res[i] = nodes[n].ends;
	}
	return res;
}
