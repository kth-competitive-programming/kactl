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
    int cnt;  
    void init(int siz_) { siz = siz_; root = 0; cnt = 0; }
    
    void insert(line& v, int l, int r, node* &nd) { 
        if(!nd) { 
            nd = new node(v); 
            cnt++; 
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
        if(nd -> f.eval(mi) > v.eval(mi)) insert(v, mi + 1, r, nd -> r); 
        else { 
            swap(nd -> f, v); 
            insert(v, l, mi, nd -> l); 
        }
    }
    void add_line(ll a, ll b) { 
        line v(a, b); 
        insert(v, -siz, siz, root); 
    } 

    ll query(ll x, int l, int r, node* &nd) { 
        if(!nd) return -inf; 
        if(l == r) return nd -> f.eval(x); 

        int mid = l + (r - l) / 2 ; 
        if(mid >= x) return max(nd -> f.eval(x), query(x, l, mid, nd -> l)); 
        return max(nd -> f.eval(x), query(x, mid + 1, r, nd -> r)); 
    }   
};