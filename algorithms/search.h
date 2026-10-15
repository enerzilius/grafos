#pragma once

#include <cstdint>
#include <map>
#include <queue>
#include <unordered_set>
#include <vector>
#include <stack>
#include "../structures/adj_list.h"

namespace gsa { // Graph Search Algorithms

void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      uint16_t beginAt = 0);
void breadthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                        uint16_t beginAt = 0);
std::vector<uint16_t> shortestPath(const std::map<uint16_t, std::vector<uint16_t>> &list, uint16_t from, uint16_t to);
void searchConnectedComponents(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    uint16_t beginAt = 0);
void kosarajuShahirSCC(
    const AdjListGraph& graph);
void precedenceScheduling(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          uint16_t beginAt = 0);
void precedenceScheduling(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          std::stack<uint16_t>& returnStack, uint16_t beginAt = 0);
void kruskalMST(const std::map<uint16_t, std::vector<uint16_t>> &list);
void lazyPrimMST(const std::map<uint16_t, std::vector<uint16_t>> &list, uint16_t begin_at = 0);
} // namespace gsa
