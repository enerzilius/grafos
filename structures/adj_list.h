#pragma once

#include <cstdint>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class AdjListGraph {
public:
  bool isUndirected = false;
  std::map<uint16_t, std::vector<uint16_t>> list;
  AdjListGraph(bool Undirected = false);
  
  ~AdjListGraph();

  void addVertex(uint16_t vertex);
  void removeVertex(uint16_t vertex);

  void addEdge(uint16_t vertex, uint16_t adjacentVertex);
  void removeEdge(uint16_t vertex, uint16_t adjacentVertex);
  
  void readFromFile(const std::string &path, bool isUndirected = false);
  
  void reverseGraph();
  void clearGraph();
  
  void print();
private:
  void removeVertexUndirected(uint16_t vertex);
  void removeVertexDirected(uint16_t vertex);
};
