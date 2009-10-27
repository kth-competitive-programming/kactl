/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest path in a graph that might have negative edge distances. Propagates negative infinity distances.
 * Time: O(E * V) where E is the number of edges and V is the number of vertices.
 * Memory: O(1)
 * Status: Working
 */
#pragma once

template <typename T>
struct Edge {
  int source;
  int destination;
  T weight;
};

template <typename T>
struct Node {
  T source_dist;
  int prev_node;
};

template <typename T>
struct Graph {
  vector<Node<T> > nodes;
  vector<Edge<T> > edges;
};

template <typename T>
void bellmanFord2(Graph<T> &graph, int start_node){
  for (int i=0; i<graph.nodes.size(); i++){
    graph.nodes[i].source_dist = numeric_limits<T>::max();
    graph.nodes[i].prev_node = -1;
  }

  graph.nodes[start_node].source_dist = 0;

  for (int i=0; i<graph.nodes.size(); i++){
    for (int j=0; j<graph.edges.size(); j++){
      Edge<T> &edge = graph.edges[j];
      Node<T> &curr = graph.nodes[edge.source];
      Node<T> &dest = graph.nodes[edge.destination];

      if (curr.source_dist != numeric_limits<T>::max()){
        T new_dist = curr.source_dist + edge.weight;
        if (new_dist < dest.source_dist){
          dest.source_dist = new_dist;
          dest.prev_node = edge.source;
          if (i >= graph.nodes.size()-1){
            dest.prev_node = -2;
          }
        }
      }
    }
  }

  for (int i=0; i<graph.nodes.size(); i++){
    for (int j=0; j<graph.edges.size(); j++){
      Edge<T> &edge = graph.edges[j];
      Node<T> &curr = graph.nodes[edge.source];
	  Node<T> &dest = graph.nodes[edge.destination];

	  if(curr.prev_node == -2) {
		  dest.source_dist = -1;
		  dest.prev_node = -2;
	  }
	}
  }
}
