#pragma once

#include <cstdint>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

struct Edge {
    uint16_t v;
    float weight;
};

class WeightedGraph {
public:
  bool isUndirected = false;
  std::map<uint16_t, std::vector<uint16_t>> list;
  WeightedGraph(bool Undirected = false);
  
  ~WeightedGraph();

  void addVertex(uint16_t vertex);
  void removeVertex(uint16_t vertex);

  void addEdge(uint16_t vertex, uint16_t adjacentVertex, float weight);
  void removeEdge(uint16_t vertex, uint16_t adjacentVertex);
  
  void readFromTextFile(const std::string &path, bool isUndirected = false);
  
  void reverseGraph();
  void clearGraph();
  
  void print();
private:
  void removeVertexUndirected(uint16_t vertex);
  void removeVertexDirected(uint16_t vertex);
};
