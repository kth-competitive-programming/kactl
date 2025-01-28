/**
 * Author: Andy Phan
 * Date: 2025-01-25
 * License: CC0
 * Source: me
 * Description: T: value/update type. DS: Stores T.
 * Same semantics as std::priority\_queue.
 * Time: O(U \log N).
 */
#pragma once

template<class T, class DS, class Compare = less<T>>
struct PQUpdate {
	DS inner;
	multimap<T, int, Compare> rev_upd;
	using iter = decltype(rev_upd)::iterator;
	vector<iter> st;
	PQUpdate(DS inner, Compare comp={}):
		inner(inner), rev_upd(comp) {}

	bool empty() { return st.empty(); }
	const T& top() { return rev_upd.rbegin()->first; }
	void push(T value) {
		inner.push(value);
		st.push_back(rev_upd.insert({value, sz(st)}));
	}
	void pop() {
		vector<iter> extra;
		iter curr = rev_upd.end();
		int min_ind = sz(st);
		do {
			extra.push_back(--curr);
			min_ind = min(min_ind, curr->second);
		} while (2*sz(extra) < sz(st) - min_ind);
		while (sz(st) > min_ind) {
			if (rev_upd.value_comp()(*st.back(), *curr))
				extra.push_back(st.back());
			inner.pop(); st.pop_back();
		}
		rev_upd.erase(extra[0]);
		for (auto it : extra | views::drop(1) | views::reverse) {
			it->second = sz(st);
			inner.push(it->first);
			st.push_back(it);
		}
	}
};
