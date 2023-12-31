"""
* Author: Yago Iglesias
* Description: Graph class. Basic structure for graphs.
"""
from collections import defaultdict


class Graph:
    def __init__(self, v, egdes=None):
        self.v = v
        self.edges = defaultdict(dict)
        if egdes:
            for u, v, w in egdes:
                self.add_edge(u, v, w)

    def add_edge(self, u, v, w):
        self.edges[u][v] = w

    def get_neighbors(self, u):
        neighbors = []
        for v in self.edges[u].keys():
            neighbors.append(v)
        return neighbors

    def get_edge(self, u, v):
        if v in self.edges[u]:
            return self.edges[u][v]
        return None

    def get_edges(self):
        edges = []
        for u in self.edges.keys():
            for v in self.edges[u].keys():
                edges.append((u, v))
        return edges
