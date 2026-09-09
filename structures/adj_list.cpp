#include "adj_list.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

AdjListGraph::AdjListGraph(bool undirectional) {
  isUndirectional = undirectional;
  list = {};
}

AdjListGraph::~AdjListGraph() { list = {}; }

void AdjListGraph::addEdge(const uint16_t vertex, uint16_t adjacentVertex) {
  list[vertex].push_back(adjacentVertex);
  list[adjacentVertex].push_back(vertex);
}

void AdjListGraph::readFromFile(const std::string &path) {
  list.clear();
  std::ifstream file(path);

  if (!file)
    std::cout << " [!] Erro ao ler o arquivo [ " << path << " ]\n";

  std::string line;

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::istringstream iss(line);

    std::string keyToken;
    if (!std::getline(iss, keyToken, ':'))
      continue;

    uint16_t key;
    try {
      key = static_cast<uint16_t>(std::stoi(keyToken));
    } catch (...) {
      continue;
    }

    std::vector<uint16_t> values;
    int v;
    while (iss >> v) {
      values.push_back(static_cast<uint16_t>(v));
    }

    list[key] = std::move(values);
  }
}

void AdjListGraph::print() {
  std::map<uint16_t, std::vector<uint16_t>>::iterator iterator;
  for (iterator = list.begin(); iterator != list.end(); iterator++) {
    std::cout << "\n" << iterator->first << ":";
    for (const uint16_t &vertex : iterator->second) {
      std::cout << " " << vertex;
    }
  }
  std::cout << "\n";
}
