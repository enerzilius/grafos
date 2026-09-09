#pragma once

#include <cstdint>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class AdjListGraph {

public:
  bool isUndirectional = false;
  std::map<uint16_t, std::vector<uint16_t>> list;
  AdjListGraph(bool undirectional = false);
  ~AdjListGraph();
  void addEdge(const uint16_t vertex, uint16_t adjacentVertex);
  void removeEdge(const uint16_t vertex, uint16_t adjacentVertex);
  void readFromFile(const std::string &path);
  void print();
};
