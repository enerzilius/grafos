#pragma once

#include <cstdint>
#include <map>
#include <unordered_set>
#include <vector>
#include <queue>

void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      const uint16_t begin_at);
static void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list, const uint16_t begin_at);
void breadthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      const uint16_t begin_at);
static void breadthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list, std::queue<uint16_t>& queue,
                 const uint16_t begin_at);