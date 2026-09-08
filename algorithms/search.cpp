#include "search.h"
#include <cstdint>
#include <map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <queue>

struct TableContents {
  bool marked;
  uint16_t edgeTo;
};

static std::map<uint16_t, TableContents> marked;

static void printTable() {
  std::cout<<"\nv | marked | edgeTo \n";
  for(auto const& [key, value] : marked) {
    std::cout<<key<<" | "<<(value.marked? "T" : "F")<<" | "<<value.edgeTo<<"\n";
  }
  std::cout<<"\n";
}

void depthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      const uint16_t begin_at = 0) {
  marked.insert({begin_at, {true, begin_at}});
  depthSearch(list, begin_at);
  printTable();
}

static void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                 const uint16_t begin_at = 0) {
  
  std::vector<uint16_t> currentVector = list.at(begin_at);
  if (currentVector.empty())
    return;

  for (const uint16_t vertex : currentVector) {
      if (marked.find(vertex) != marked.end())
      continue;
    marked.insert({vertex, {true, begin_at}});
    
    depthSearch(list, vertex);
  }
}

void breadthFirstSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                      const uint16_t begin_at = 0) {
  std::queue<uint16_t> queue;
  
  queue.push(begin_at);
  marked.insert({begin_at, {true, begin_at}});
  breadthSearch(list, queue, begin_at);
  printTable();
}

static void breadthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list, std::queue<uint16_t>& queue,
                 const uint16_t begin_at = 0) {
  
  std::vector<uint16_t> currentVector = list.at(begin_at);
  if (currentVector.empty())
    return;

  for (const uint16_t vertex : currentVector) {
    if (marked.find(vertex) != marked.end())
      continue;
    
    queue.push(vertex);
    marked.insert({vertex, {true, begin_at}});
  }
  breadthSearch(list, queue, queue.front());
}
