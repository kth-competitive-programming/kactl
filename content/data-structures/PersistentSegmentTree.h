/**
 * Author:
 * Description: Point update (addition), range sum query
 * Usage: Unknown, but just declare sufficient size. You should achieve root number manually after every query/update.
 */
#pragma once

struct PersistentSegmentTree {
    int size;
    int last_root;
    vector<ll> tree, l, r;
    
    PersistentSegmentTree(int _size) {
        size = _size;
        init(0, size-1);
        last_root = 0;
    }

    void add_node() {
        tree.push_back(0);
        l.push_back(-1);
        r.push_back(-1);
    }
    
    int init(int nl, int nr) {
        int n = tree.size();
        add_node();
        if (nl == nr) {
            tree[n] = 0;
            return n;
        }
        int mid = (nl + nr) / 2;
        l[n] = init(nl, mid);
        r[n] = init(mid+1, nr);
        return n;
    }

    void update(int ori, int pos, int val, int nl, int nr) {
        int n = tree.size();
        add_node();
        if (nl == nr) {
            tree[n] = tree[ori] + val;
            return;
        }

        int mid = (nl + nr) / 2;
        if (pos <= mid) {
            l[n] = tree.size();
            r[n] = r[ori];
            update(l[ori], pos, val, nl, mid);
        } else {
            l[n] = l[ori];
            r[n] = tree.size();
            update(r[ori], pos, val, mid+1, nr);
        }
        tree[n] = tree[l[n]] + tree[r[n]];
    }

    void update(int pos, int val) {
        int new_root = tree.size();
        update(last_root, pos, val, 0, size-1);
        last_root = new_root;
    }

    ll query(int a, int b, int n, int nl, int nr) {
        if (n == -1) return 0;
        if (b < nl || nr < a) return 0;
        if (a <= nl && nr <= b) return tree[n];
        int mid = (nl + nr) / 2;
        return query(a, b, l[n], nl, mid) + query(a, b, r[n], mid+1, nr);
    }

    ll query(int x, int root) {
        return query(0, x, root, 0, size-1);
    }
};
