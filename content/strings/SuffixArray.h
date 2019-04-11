/**
 * Author: chilli
 * Date: 2009-10-27
 * License: CC0
 * Source: MIT Notebook
 * computation in suffix arrays and its applications (2001).
 * Description: Builds suffix array for a string. $sa[i]$ is
 * the starting index of the suffix which is $i$-th in the
 * sorted suffix array. The returned vector is of size
 * $n+1$, and $sa[0] = n$. The {\tt lcp} function calculates
 * longest common prefixes for neighbouring strings in
 * suffix array. The returned vector is of size $n+1$, and
 * $ret[0] = 0$. Time: $O(N)$ where $N$ is the length of the
 * string for creation of the SA. $O(N)$ for longest common
 * prefixes. Memory: $O(N)$ Status: Tested on UVa Live 4513
 */
#pragma once

struct SuffixArray {
    vi sa, lcp;
    int cmp(int *r, int a, int b, int l) {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    SuffixArray(string &s, int lim = 256) {
        int n = sz(s) + 1;
        vi wa(2 * n), wb(2 * n), wv(n), ws(max(n, lim));
        sa.resize(n);
        int *x = wa.data(), *y = wb.data();
        rep(i, 0, n) ws[x[i] = s[i]]++;
        rep(i, 1, lim) ws[i] += ws[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--ws[x[i]]] = i;
        for (int j = 1, p = 0; p < n; j *= 2, lim = p) {
            p = 0;
            rep(i, n - j, n) y[p++] = i;
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            rep(i, 0, n) wv[i] = x[y[i]];
            rep(i, 0, lim) { ws[i] = 0; }
            rep(i, 0, n) ws[wv[i]]++;
            rep(i, 1, lim) ws[i] += ws[i - 1];
            for (int i = n - 1; i >= 0; i--)
                sa[--ws[wv[i]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) x[sa[i]] =
                cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
        }
        // LCP: res[i] = lcp(a[i], a[i-1])
        lcp.resize(n);
        vi rank(n);
        int j, k = 0;
        rep(i, 1, n) rank[sa[i]] = i;
        for (int i = 0; i < n - 1; lcp[rank[i++]] = k)
            for (k ? k-- : 0, j = sa[rank[i] - 1];
                 s[i + k] == s[j + k]; k++)
                ;
    }
};