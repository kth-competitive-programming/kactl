/**
 * Author: Ahmed Dardery
 * Date: 2020-12-24
 * License: CC0
 * Source: https://codeforces.com/blog/entry/13959
 * Description: Builds a palindromic tree over a string
 * 0 is the imaginary string, 1 is the empty string
 * [2, n) are the palindromes, s.substr(pos[i], len[i]), occurs freq[i]
 * fail[i] is the longest suffix palindrome of ith palindrome
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

struct PalinTree {
  const int A = 128;
  string str;
  vi fail, len, pos, lz, freq;
  vector<vi> nxt;
  int n, cur;
 
  PalinTree(const string &s) : str(s) {
    fail = len = pos = lz = freq = vi(sz(s) + 2);
    nxt.resize(sz(s) + 2);
    n = cur = fail[0] = fail[1] = 0;
    addNode(-1, -1), addNode(0, 0);
    rep(i, 0, sz(s)) addChar(i, s[i]);
    propagate();
  }
 
  void addChar(int i, int c) {
    int u = getFailure(cur, i);
    int &ch = nxt[u][c];
    if (~ch) return (void) ++lz[cur = ch];
    int v = cur = ch = addNode(len[u] + 2, i - len[u] - 1);
    fail[v] = len[v] == 1 ? 1 : nxt[getFailure(fail[u], i)][c];
  }
 
  int addNode(int l, int p) {
    nxt[n].assign(A, -1);
    len[n] = l, pos[n] = p, lz[n] = 1, freq[n] = 0;
    return n++;
  }
 
  void propagate() {
    for (int i = n - 1; ~i; --i) {
      freq[i] += lz[i];
      lz[fail[i]] += lz[i];
      lz[i] = 0;
    }
  }
 
  int getFailure(int u, int i) {
    while (i <= len[u] || str[i] != str[i - len[u] - 1]) u = fail[u];
    return u;
  }
};
 
