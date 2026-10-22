#include "weighted_graph.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

WeightedGraph::WeightedGraph(bool Undirected) {
  isUndirected = Undirected;
  list = {};
}

WeightedGraph::~WeightedGraph() { list = {}; }

void WeightedGraph::addVertex(uint16_t vertex) {
  list[vertex] = std::vector<Edge>();
}

void WeightedGraph::addEdge(uint16_t vertex, Edge edge, float weight) {
  list[vertex].push_back(edge);
  if (isUndirected) {
    if (!list[edge.v].empty()) {
      Edge edge2 = {.v = vertex, .weight = edge.weight};
      list[edge.v].push_back(edge2);
    }
    else
      list[edge.v] = std::vector<Edge>();
  }
}

void WeightedGraph::readFromTextFile(const std::string &path, bool undirected) {
    isUndirected = undirected;
    list.clear();

    std::ifstream file(path);
    if (!file) {
        std::cout << " [!] Error reading file: [ " << path << " ]\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::istringstream iss(line);

        int from, to;
        float weight;

        // Skip malformed lines
        if (!(iss >> from >> to >> weight))
            continue;

        auto u = static_cast<uint16_t>(from);
        auto v = static_cast<uint16_t>(to);

        list[u].push_back({v, weight});

        if (undirected) {
            list[v].push_back({u, weight});
        } else {
            // Make sure the destination node exists in the map,
            // even if it has no outgoing edges
            list[v];
        }
    }
}

void WeightedGraph::print() {
  std::map<uint16_t, std::vector<Edge>>::iterator iterator;
  std::cout<<"\nADJACENCY LIST GRAPH\n";
  for (iterator = list.begin(); iterator != list.end(); iterator++) {
    if (iterator->second.empty())
      continue;
    
    for (const Edge &edge : iterator->second) {
      std::cout << iterator->first << " " << edge.v << " " << edge.weight <<"\n";
    }
  }
  std::cout << "\n";
}

void WeightedGraph::reverseGraph() {
  if (isUndirected)
    return;

  std::map<uint16_t, std::vector<Edge>> reversed;

  for (auto &[vertex, value] : list) {
    if (reversed[vertex].empty())
      reversed[vertex] = std::vector<Edge>();
    for (auto it = value.begin(); it != value.end(); ++it) {
      Edge edge{.v = vertex, .weight = it->weight};
      reversed[it->v].push_back(edge);
    }
  }

  list = std::move(reversed);
}

void WeightedGraph::clearGraph() {
  list.clear();
  isUndirected = false;
}
