#pragma once

#include <cstdint>
#include <map>
#include <queue>
#include <unordered_set>
#include <vector>

namespace gsa { // Graph Search Algorithms

void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      const uint16_t begin_at);
void breadthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                        const uint16_t begin_at);

} // namespace gsa
