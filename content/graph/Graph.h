/**
 * Author: Chen Xing
 * Date: .2009-04-09
 * Source:
 * Description: Basic node/edge/graph structures.
 * Status: Tested
 */
#pragma once

struct Node {
	// <destination node, edge number>
	// Might be exchanged with vector<pair> or map instead.
	typedef multimap<int, int> OutsT;

	// Outgoing edges.
	OutsT outs;
};

struct Edge {
	// Source node.
	int a;

	// Destination node.
	int b;

	// Flag set for bidirectional edges.
	bool bidir;
};

template<class N, class E>
struct Graph {
	typedef N NodeT;
	typedef E EdgeT;

	vector<N> nodes;
	vector<E> edges;
};
