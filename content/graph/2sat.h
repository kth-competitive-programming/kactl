/**
 * Author: Emil Lenngren
 * Date: 2011-11-29
 * Source:
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or reports that it is unsatisfiable.
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.add_clause(0, true, 3, false); // Variable 0 must be true or variable 3 must be false (or both)
 *  ts.set_value(2, true); // We already know that variable 2 must be true
 *  ts.solve(); // Returns true if it is solvable, otherwise false
 *  ts.values[0..N-1] holds all the assigned values to the variables
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 */
#pragma once

#include <vector>

using namespace std;

struct TwoSat {
        vector<char> values; //0 = false, 1 = true
        int N;
        
        struct Node {
                vi ins, outs;
                int comp_id, vis;
                Node() : vis(0) {}
        };
        vector<Node> nodes;
        
        TwoSat(int n) : values(n), N(n), nodes(2*n) {}
        
        void add_clause(int a_index, bool a_value, int b_index, bool b_value){
                int a = 2*a_index + a_value, b = 2*b_index + b_value;
                nodes[a^1].outs.push_back(b), nodes[b].ins.push_back(a^1);
                nodes[b^1].outs.push_back(a), nodes[a].ins.push_back(b^1);
        }
        
        void set_value(int index, bool value){
                add_clause(index, value, index, value);
        }
        
        struct Comp {
                vi nodes;
                bool value;
                Comp() : value(0) {}
        };
        vector<Comp> comp;
        vi st;
        
        void dfs1(int v){
                Node& n = nodes[v];
                if (n.vis) return;
                n.vis = 1;
                trav(it, n.outs) dfs1(*it);
                st.push_back(v);
        }
        
        void dfs2(int v){
                nodes[v].vis = 1;
                nodes[v].comp_id = comp.size()-1;
                comp.back().nodes.push_back(v);
                trav(it, nodes[v].ins) if (!nodes[*it].vis) dfs2(*it);
        }
        
        bool solve(){
                st.reserve(2*N);
                rep(i, 0, 2*N) dfs1(i);
                rep(i, 0, 2*N) nodes[i].vis = 0;
                while(!st.empty()){
                        if (!nodes[st.back()].vis){
                                comp.push_back(Comp());
                                dfs2(st.back());
                        }
                        st.pop_back();
                }
                trav(it, comp){
                        if (it->value == 0){
                                Comp& c = comp[nodes[it->nodes.front()^1].comp_id];
                                if (&c == &*it) return 0;
                                c.value = 1;
                                trav(n, it->nodes) values[*n/2] = !(*n%2);
                        }
                }
                return 1;
        }
};
