/**
 * Author: Chen Xing
 * Date: 2009-04-09
 * Source:
 * Description: Basic node/edge/graph structures for DijkstraPrimAstar.
 * Status: Tested
 */
#pragma once

#include "Graph.hpp"

template<class D>
struct NodeDPAB : Node {
	typedef D DistanceT;
	D srcDist; //! Calculated distance from source node.
	//! Calculated previous node when walking from source node.
	int srcPrev;
};

template<class D>
struct EdgeDPAB : Edge {
	typedef D DistanceT;
	D dist; //! Distance from source to destination.
};
