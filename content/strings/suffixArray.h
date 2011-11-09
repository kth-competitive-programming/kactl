/**
 * Author: Lukas Polacek
 * Date: 2009-10-27
 * Source: folklore and Linear-time longest-common-prefix
 * computation in suffix arrays and its applications (2001).
 * Description: Builds suffix array for a string. $res[i]$ is
 * the starting index of the suffix which is $i$-th in the
 * sorted suffix array. Empty string appears on the first
 * position. lcp function calculates longest common
 * prefixes for neighbouring strings in suffix array.
 * Time: $O(N \log N)$ where $N$ is the length of the string
 * for creation of the SA. $O(N)$ for longest common prefixes.
 * Memory: $O(N)$
 * Status: Tested on UVa Live 4513
 */
#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <numeric>
using namespace std;

typedef pair<int, int> pii;
void count_sort(vector<pii> &b, int bits) {
	//this is just 3 times faster than stl sort for N=10^6
	int mask = (1 << bits) - 1;
	for (int it = 0; it < 2; it++) {
		int move = it * bits;
		vector<int> q(1 << bits, 0), w(q.size() + 1, 0);
		for (unsigned i = 0; i < b.size(); i++)
			q[(b[i].first >> move) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pii> res(b.size());
		for (unsigned i = 0; i < b.size(); i++)
			res[w[(b[i].first >> move) & mask]++] = b[i];
		swap(b, res);
	}
}
struct SuffixArray {
	vector<int> a;
	string s;
	SuffixArray(string _s) {
		s = _s + '\0';
		vector<pii> b(s.size());
		a.resize(s.size());
		for (unsigned i = 0; i < s.size(); i++) {
			b[i].first = s[i];
			b[i].second = i;
		}

		unsigned q = 8;
		while ((1 << q) < s.size()) q++;
		for (int moc = 0;; moc++) {
			count_sort(b, q);
			a[b[0].second] = 0;
			for (unsigned i = 1; i < s.size(); i++)
				a[b[i].second] = a[b[i - 1].second] +
					(b[i - 1].first != b[i].first);

			if ((1 << moc) >= s.size()) break;
			for (unsigned i = 0; i < s.size(); i++) {
				b[i].first = a[i] << q;
				if (i + (1 << moc) < s.size())
					b[i].first += a[i + (1 << moc)];
				b[i].second = i;
			}
		}
		for (size_t i = 0; i < a.size(); i++)
			a[i] = b[i].second;
	}
	vector<int> lcp() {
		//longest common prefix of two neighbouring strings in SA
		int n = a.size();
		vector<int> inv(n), res(n);
		for (int i = 0; i < n; i++) inv[a[i]] = i;
		for (int i = 0, h = 0; i < n; i++) if (inv[i] > 0) {
			int p0 = a[inv[i] - 1];
			while (s[i + h] == s[p0 + h]) h++;
			res[inv[i]] = h;
			if(h > 0) h--;
		}
		return res;
	}
};
