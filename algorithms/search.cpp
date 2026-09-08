#include "search.h"
#include <cstdint>
#include <map>
#include <unordered_set>
#include <vector>
#include <iostream>

struct TableContents {
  bool marked;
  uint16_t edgeTo;
};

static std::map<uint16_t, TableContents> markedTable;

static void printTable() {
  std::cout<<"v | marked | edgeTo \n";
  for(auto const& [key, value] : markedTable) {
    std::cout<<key<<" | "<<(value.marked? "T" : "F")<<" | "<<value.edgeTo<<"\n";
  }
}

void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      uint16_t begin_at = 0) {
  std::unordered_set<uint16_t> marked;
  uint32_t count = 0;

  markedTable.insert({begin_at, {true, begin_at}});
  depthSearch(list, count, marked, begin_at);
  printTable();
}

void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                 uint32_t &count, std::unordered_set<uint16_t> &marked,
                 const uint16_t begin_at = 0) {
  marked.insert(begin_at);
  count++;
  
  std::vector<uint16_t> currentVector = list.at(begin_at);
  if (currentVector.empty())
    return;

    for (const uint16_t vertex : currentVector) {
      if (marked.find(vertex) != marked.end())
      continue;
    markedTable.insert({vertex, {true, begin_at}});
      
    marked.insert(vertex);
    count++;
    
    depthSearch(list, count, marked, vertex);
  }
}


