/**
 * Author: Julio (real source radoslav11)
 * Date: 2026-11-05
 * License: CC0
 * Source: own work
 * Description: Container (seg tree like) where you can add lines of the form kx+m, and query maximum values at points x.
 * Time: O(\log N)
 * Status: tested on CF932F (Escape Through Leaf)
 */
#pragma once
struct line { 
    ll a, b; 
    line(ll a = 0, ll b = 0) : a(a), b(b) { }
    ll eval(ll x) { return  1LL * a * x + b ; }
};
const ll inf = 1LL << 62; 
struct LiChao { 
    struct node { 
        node *l, *r; 
        line f; 
        node(ll a = 0, ll b = 0) : f(a, b), l(0), r(0) { }
        node(line v) { f = v; l = r = 0; }
    };
    node *root; 
    int siz;
    void init(int siz_) { siz = siz_; root = 0; }
    
    void insert(node* &nd, line& v, int l, int r) { 
        if(!nd) { 
            nd = new node(v); 
            return; 
        }
        ll tl = nd -> f.eval(l), tr = nd -> f.eval(r); 
        ll vl = v.eval(l), vr = v.eval(r);
        if(tl >= vl && tr >= vr) return; 
        if(tl < vl && tr < vr) { 
            nd -> f = v; 
            return; 
        }
        ll mi = l + (r - l) / 2; 
        if(tl < vl) swap(nd -> f, v); 
        if(nd -> f.eval(mi) > v.eval(mi)) insert(nd -> r, v, mi + 1, r); 
        else { 
            swap(nd -> f, v); 
            insert(nd -> l, v, l, mi); 
        }
    }
    void add_line(ll a, ll b) { 
        line v(a, b); 
        insert(root, v, -siz, siz); 
    } 

    ll query(ll x, int l, int r, node* &nd) { 
        if(!nd) return -inf; 
        if(l == r) return nd -> f.eval(x); 

        int m = l + (r - l) / 2 ; 
        if(m >= x) return max(nd -> f.eval(x), query(x, l, m, nd -> l)); 
        return max(nd -> f.eval(x), query(x, m + 1, r, nd -> r)); 
    }   
};