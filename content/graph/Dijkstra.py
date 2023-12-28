"""
* Author: Yago Iglesias
* Description: Dijkstra's algorithm for finding the shortest path between two vertices in a graph.
* Time: O(E log V)
"""

from queue import PriorityQueue


def dijkstra(graph, start_vertex, end_vertex):
    visited = [False for _ in range(graph.v)]
    distance = [float("inf") for _ in range(graph.v)]
    distance[start_vertex] = 0

    pq = PriorityQueue()
    pq.put((0, start_vertex))

    while not pq.empty():
        _, current_vertex = pq.get()
        visited[current_vertex] = True
        for neighbor in graph.get_neighbors(current_vertex):
            if not visited[neighbor]:
                distance[neighbor] = min(
                    distance[neighbor],
                    distance[current_vertex] + graph.get_edge(current_vertex, neighbor),
                )
                pq.put((distance[neighbor], neighbor))

    return distance[end_vertex]
