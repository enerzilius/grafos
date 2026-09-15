#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <queue>
#include <unordered_set>

namespace gsa { // Graph Search Algorithms

void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      uint16_t beginAt = 0);
void breadthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                        uint16_t beginAt = 0);
void searchConnectedComponents(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    uint16_t beginAt = 0);
void precedenceScheduling(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          uint16_t beginAt);
} // namespace gsa
