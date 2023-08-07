#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

// This class represents a graph.
class Graph {
public:
  // Constructor.
  Graph(int n) {
    vertices_ = n;
    edges_ = vector<vector<int>>(vertices_, vector<int>());
    weights_.resize(vertices_, vector<int>(vertices_));
  }

  // Add an edge to the graph.
  void add_edge(int u, int v, int w) {
    edges_[u].push_back(v);
    edges_[v].push_back(u);
    weights_[u][v] = w;
    weights_[v][u] = w;
  }

  // Get the number of vertices.
  int num_vertices() const {
    return vertices_;
  }

  // Get the adjacency list for a vertex.
  const vector<int> &adj(int u) const {
    return edges_[u];
  }

  // Get the weight of an edge.
  int weight(int u, int v) const {
    return weights_[u][v];
  }

private:
  int vertices_;
  std::vector<std::vector<int>> edges_;
  std::vector<std::vector<int>> weights_;
};

// This function finds the shortest path from the source vertex `s` to all other vertices in the graph `g`.
// The distance between two vertices `u` and `v` is stored in the array `distances`.
// The path from `s` to `v` is stored in the array `predecessors`.
void dijkstra(const Graph &g, int s, vector<int> &distances, vector<int> &predecessors) {
  // Initialize the distances and predecessors.
  for (int v = 0; v < g.num_vertices(); v++) {
    distances[v] = INT_MAX;
    predecessors[v] = -1;
  }

  // Set the distance to the source vertex to 0.
  distances[s] = 0;

  // Create a priority queue to store the vertices that are still to be processed.
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
  queue.push({0, s});

  // While the queue is not empty, do the following:
  while (!queue.empty()) {
    // Pop the vertex with the minimum distance from the queue.
    int u = queue.top().second;
    queue.pop();

    // For each neighbor `v` of `u`, do the following:
    for (int v : g.adj(u)) {
      // If the distance to `v` through `u` is less than the current distance to `v`, do the following:
      if (distances[v] > distances[u] + g.weight(u, v)) {
        distances[v] = distances[u] + g.weight(u, v);
        predecessors[v] = u;
        queue.push({distances[v], v});
      }
    }
  }
}

// This function prints the shortest path from the source vertex `s` to the destination vertex `d`.
std::string print_path(const Graph &g, int s, int d, vector<int> &predecessors) {
  // If the destination vertex is not reachable from the source vertex, do the following:
  if (predecessors[d] == -1) {
    std::cout << "No path from " << s << " to " << d << endl;
    return "none";
  }

  // Create a vector to store the vertices on the path.
  vector<int> path;
  int u = d;
  while (u != -1) {
    path.push_back(u);
    u = predecessors[u];
  }

  // Reverse the order of the vertices in the vector.
  reverse(path.begin(), path.end());

  std::string result("");

  // Print the vertices on the path.
  for (int v : path) {
    result += std::to_string(v) + " ";
  }

  return result;
}

/*
TEST(SimpleGraphInitTest, PositiveNos) { 

  ASSERT_EQ("1 3 4 ", path);
}
*/
 
int main(int argc, char **argv) {

  auto numberVertices = 6;
  Graph g(numberVertices);

  g.add_edge(0, 1, 7);
  g.add_edge(0, 2, 9);
  g.add_edge(0, 5, 14);
  g.add_edge(1, 2, 10);
  g.add_edge(1, 3, 15);
  g.add_edge(2, 5, 2);
  g.add_edge(2, 3, 11);
  g.add_edge(3, 4, 6);
  g.add_edge(4, 5, 9);

  vector<int> distances(numberVertices, INT_MAX);
  vector<int> predecessors(numberVertices, -1);

  dijkstra(g, 0, distances, predecessors);
  std::cout << print_path(g, 0, 3, predecessors) << std::endl;

  //testing::InitGoogleTest(&argc, argv);
  //return RUN_ALL_TESTS();
  return 0;
}
