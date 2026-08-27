#pragma once

#include <cstdint>
#include <map>
#include <unordered_set>
#include <vector>

void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      uint16_t begin_at);
void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                 uint32_t &count, std::unordered_set<uint16_t> &marked,
                 uint16_t begin_at);
