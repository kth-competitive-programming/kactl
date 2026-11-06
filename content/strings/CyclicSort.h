/**
 * Author: Julio
 * Source: cp-algo 
 * Description: Sort string cyclic shifts 
 * Time: O(NlogN)
 * Status: tested
 */
#pragma once
vi sort_cyclic_shifts(const string& s) {
    int n = s.size();
    const int alphabet = 256;
    vi p(n), c(n), cnt(max(alphabet, n), 0);
    rep(i,0,n) cnt[s[i]]++;
    rep(i,1,alphabet) cnt[i] += cnt[i-1];
    rep(i,0,n) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    rep(i,1,n) {
        if (s[p[i]] != s[p[i-1]]) classes++;
        c[p[i]] = classes - 1;
    }
    vi pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        rep(i,0,n) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        rep(i,0,n) cnt[c[pn[i]]]++;
        rep(i,1,classes) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        rep(i,1,n) {
            pii cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pii prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev) ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}