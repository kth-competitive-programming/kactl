/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once
const int M = 1e9 + 7;
 
typedef struct item * pitem;
struct item {
    int prior, cnt, value, b = 1, c = 0, sum = 0;
    pitem l, r;
    bool rev = false;
    item(int val): value(val), prior(rand()), cnt(0), l(NULL), r(NULL) {}
};
int cnt(pitem it) { return it ? it->cnt : 0; }
int giveSum(pitem it) { return it ? it->sum : 0; }
void combineLazy(pitem t, int b, int c) {
    t->value = ((t->value * b) % M + c) % M;
    t->b = (t->b * b) % M;
    t->c = ((t->c * b) + c) % M;
} 
void push(pitem it) {
    if(it && it->rev) {
        it->rev = false;
        swap(it->l, it->r);
        if(it->l) it->l->rev ^= 1;
        if(it->r) it->r->rev ^= 1;
    }
    if(it) {
        if(it->l) combineLazy(it->l, it->b, it->c);
        if(it->r) combineLazy(it->r, it->b, it->c);
        it->sum = ((it->sum * it->b) % M + (it->cnt * it->c) % M) % M;
        it->b = 1, it->c = 0;
    }
}
void pull(pitem it) {
	if (!it) { return; }
	push(it->l), push(it->r);
	it->cnt = cnt(it->l) + cnt(it->r) + 1;
	it->sum = (giveSum(it->l) + giveSum(it->r) + it->value) % M;
}
void merge(pitem &t, pitem l, pitem r) {
    push(l), push(r);
    if(!l || !r) t = l ? l : r;
    else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    pull(t);
}
void split(pitem t, pitem &l, pitem &r, int key, int add = 0) {
    if(!t) return void(l = r = 0);
    push(t);
    int curr_key = add + cnt(t->l);
    if(key <= curr_key) split(t->l, l, t->l, key, add), r = t;
    else split(t->r, t->r, r, key, curr_key + 1), l = t;
    pull(t);
}
void insert(pitem &t, pitem new_item, int pos) {
    pitem t1 = NULL, t2 = NULL;
    split(t, t1, t2, pos);
    merge(t1, t1, new_item);
    merge(t, t1, t2);
}
void remove(pitem &t, int pos) {
    pitem t1 = NULL, t2 = NULL, t3 = NULL;
    split(t, t1, t3, pos);
    split(t3, t2, t3, 1);
    merge(t, t1, t3);
}