#pragma once

#include "../structures/adj_list.h"
#include "../structures/weighted_graph.h"
#include <cstdint>
#include <map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

namespace gsa { // Graph Search Algorithms
// UNWEIGHTED
void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      uint16_t beginAt = 0);

void breadthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                        uint16_t beginAt = 0);

std::vector<uint16_t>
shortestPath(const std::map<uint16_t, std::vector<uint16_t>> &list,
             uint16_t from, uint16_t to);

void searchConnectedComponents(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    uint16_t beginAt = 0);

void kosarajuShahirSCC(const AdjListGraph &graph);

void precedenceScheduling(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          uint16_t beginAt = 0);
void precedenceScheduling(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          std::stack<uint16_t> &returnStack,
                          uint16_t beginAt = 0);

void kruskalMST(const std::map<uint16_t, std::vector<uint16_t>> &list);
void lazyPrimMST(const std::map<uint16_t, std::vector<uint16_t>> &list,
                 uint16_t begin_at = 0);
double closenessCentrality(std::map<uint16_t, std::vector<uint16_t>> &list,
                           uint16_t node = 0);

std::map<uint16_t, double>
eccentricities(const std::map<uint16_t, std::vector<uint16_t>> &list);

// ---------------------------
// WEIGHTED OPERATIONS
void precedenceScheduling(const std::map<uint16_t, std::vector<Edge>> &list,
                          uint16_t beginAt = 0);
void precedenceScheduling(const std::map<uint16_t, std::vector<Edge>> &list,
                          std::stack<uint16_t> &returnStack,
                          uint16_t beginAt = 0);
void dijkstraShortestPath(std::map<uint16_t, std::vector<Edge>> &list,
                          uint16_t from = 0);
} // namespace gsa
