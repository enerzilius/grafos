#pragma once

#include <cstdint>
#include <map>
#include <queue>
#include <unordered_set>
#include <vector>

class SearchAlgorithms {
  void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                   const uint16_t begin_at);
  void breadthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                     std::queue<uint16_t> &queue, const uint16_t begin_at);

public:
  void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                        const uint16_t begin_at);
  void breadthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          const uint16_t begin_at);
  void printTable();
};
