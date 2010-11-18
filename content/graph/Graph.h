/**
 * Author: Chen Xing
 * Date: 2009-04-09
 * Source:
 * Description: Basic node/edge/graph structures.
 * Status: Tested
 */
#pragma once

#include <map>
#include <vector>
using namespace std;

struct Node {
	// <destination node, edge number>
	// Might be exchanged with vector<pair> or map instead.
	typedef multimap<int, int> OutsT;
	OutsT outs; // Outgoing edges.
};

struct Edge {
	int a; // Source node.
	int b; // Destination node.
	bool bidir; // Flag set for bidirectional edges.
};

template<class N, class E>
struct Graph {
	typedef N NodeT;
	typedef E EdgeT;
	vector<N> nodes;
	vector<E> edges;
};
