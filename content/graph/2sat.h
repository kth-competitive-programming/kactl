/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * Source:
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or reports that it is unsatisfiable.
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.add_clause(0, true, 3, false); // Var 0 is true or var 3 is false (or both)
 *  ts.set_value(2, true); // Var 2 is true
 *  ts.at_most_one({0,1,2}); // <= 1 of vars 0, 1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 */
#pragma once

#include <vector>

using namespace std;

struct TwoSat {
	int N;
	vector<vi> gr;
	vi values; // 0 = false, 1 = true

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	int add_var() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}

	void add_clause(int a_index, bool a_value, int b_index, bool b_value) {
		int a = 2*a_index + a_value, b = 2*b_index + b_value;
		gr[a^1].push_back(b);
		gr[b^1].push_back(a);
	}

	void set_value(int index, bool value) { // (optional)
		add_clause(index, value, index, value);
	}

	void at_most_one(const vi& li, bool val=1) { // (optional)
		if (sz(li) <= 1) return;
		int cur = li[0];
		rep(i,2,sz(li)) {
			int next = add_var();
			add_clause(cur, !val, li[i], !val);
			add_clause(cur, !val, next, val);
			add_clause(li[i], !val, next, val);
			cur = next;
		}
		add_clause(cur, !val, li[1], !val);
	}

	vi orig, low, col, z;
	void dfs(int j, int& time) {
		low[j] = orig[j] = time++; col[j] = 1; z.push_back(j);
		trav(e, gr[j])
			if (col[e] == 0) {
				dfs(e, time);
				low[j] = min(low[j], low[e]);
			}
			else if (col[e] == 1)
				low[j] = min(low[j], orig[e]);
		time++;
		if (orig[j] == low[j]) for (;;) {
			int x = z.back(); z.pop_back();
			if (values[x>>1] == -1)
				values[x>>1] = x&1;
			col[x] = time;
			if (x == j) break;
		}
	}

	bool solve() {
		int time = 0;
		values.assign(N, -1);
		low.assign(2*N, 0); col = orig = low;
		rep(i,0,2*N) if (!col[i]) dfs(i, time);
		rep(i,0,N) if (col[2*i] == col[2*i+1]) return 0;
		return 1;
	}
};
