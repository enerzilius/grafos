#pragma once

#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <cstdlib>

class AdjListGraph {
    bool isUndirectional = false;
    std::map<uint16_t, std::vector<uint16_t>> list;
public:
    AdjListGraph(bool undirectional);
    ~AdjListGraph();
    void addEdge(const uint16_t vertex, uint16_t adjacentVertex);
    void addVertex(const uint16_t vertex);
    void removeVertex(const uint16_t vertex);
    void removeEdge(const uint16_t vertex, uint16_t adjacentVertex);
    void readFromFile(const std::string& path);
    void print();
};
