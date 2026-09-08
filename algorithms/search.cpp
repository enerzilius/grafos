#include "search.h"
#include <cstdint>
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

struct TableContents {
  bool marked;
  uint16_t edgeTo;
};

static std::map<uint16_t, TableContents> markedTable;

void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      uint16_t begin_at = 0) {
  std::unordered_set<uint16_t> marked;
  uint32_t count = 0;

  depthSearch(list, count, marked, begin_at);
}

void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                 uint32_t &count, std::unordered_set<uint16_t> &marked,
                 const uint16_t begin_at = 0) {
  marked.insert(begin_at);
  std::cout << begin_at << " -> ";
  count++;
  
  std::vector<uint16_t> currentVector = list.at(begin_at);
  if (currentVector.empty())
    return;

    for (const uint16_t vertex : currentVector) {
      if (marked.find(vertex) != marked.end())
      continue;
    markedTable.insert(vertex, {true, begin_at});
      
    marked.insert(vertex);
    count++;
    
    depthSearch(list, count, marked, vertex);
  }
}

static void printTable() {

}
