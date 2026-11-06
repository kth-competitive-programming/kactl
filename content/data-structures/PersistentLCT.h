struct line { 
    ll a, b; 
    line(ll a = 0, ll b = 0) : a(a), b(b) { }
    ll eval(ll x) { return  1LL * a * x + b ; }
};
const ll inf = 1LL << 62; 
struct PersistentLiChao { 
    struct node { 
        node *l, *r; 
        line f; 
        node(ll a = 0, ll b = 0) : f(a, b), l(0), r(0) { }
        node(line v) { f = v; l = r = 0; }
    };
    int siz;
    PersistentLiChao(int siz_) { siz = siz_; } 
    node *clone(node *t) { 
        return new node(*t); 
    }
    node* insert(node* nd, line v, int l, int r) { 
        if(!nd) { 
            return new node(v);  
        }
        ll tl = nd -> f.eval(l), tr = nd -> f.eval(r); 
        ll vl = v.eval(l), vr = v.eval(r);
        if(tl >= vl && tr >= vr) return nd; 

        // modify the node
        node *cur = clone(nd); 
        if(tl < vl && tr < vr) { 
            cur -> f = v; 
            return cur; 
        }
        ll mi = l + (r - l) / 2; 
        if(tl < vl) swap(cur -> f, v); 
        if(cur -> f.eval(mi) > v.eval(mi)) { 
            cur -> r = insert(cur -> r, v, mi + 1, r); 
        } else { 
            swap(cur -> f, v);
            cur -> l = insert(cur -> l, v, l, mi); 
        }
        return cur; 
    }

    node* add_line(node* root, ll a, ll b) { 
        line v(a, b); 
        return insert(root, v, -siz, siz); 
    } 

    ll query(node *nd, ll x, int l, int r) { 
        if(!nd) return -inf; 
        if(l == r) return nd -> f.eval(x); 

        int mid = l + (r - l) / 2 ; 
        if(mid >= x) return max(nd -> f.eval(x), query(nd -> l, x, l, mid)); 
        return max(nd -> f.eval(x), query(nd -> r, x, mid + 1, r)); 
    }   
    ll query(node *nd, ll x) { 
        return query(nd, x, -siz, siz); 
    }
};