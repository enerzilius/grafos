#include "search.h"
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

struct TableContents {
  bool marked;
  uint16_t edgeTo;
};

static std::map<uint16_t, TableContents> marked;

void SearchAlgorithms::printTable() {
  std::cout << "\nv | marked | edgeTo \n";
  for (auto const &[key, value] : marked) {
    std::cout << key << " | " << (value.marked ? "T" : "F") << " | "
              << value.edgeTo << "\n";
  }
  std::cout << "\n";
}

void SearchAlgorithms::depthFirstSearch(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    const uint16_t begin_at = 0) {
  marked.clear();
  marked.insert({begin_at, {true, begin_at}});
  depthSearch(list, begin_at);
  printTable();
}

void SearchAlgorithms::depthSearch(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
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

void SearchAlgorithms::breadthFirstSearch(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    const uint16_t begin_at = 0) {
  std::queue<uint16_t> queue;
  marked.clear();
  queue.push(begin_at);
  marked.insert({begin_at, {true, begin_at}});
  breadthSearch(list, queue, begin_at);
  printTable();
}

void SearchAlgorithms::breadthSearch(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    std::queue<uint16_t> &queue, const uint16_t begin_at = 0) {

  std::vector<uint16_t> currentVector = list.at(begin_at);

  if (currentVector.empty() || queue.empty())
    return;

  queue.pop();

  for (const uint16_t vertex : currentVector) {
    if (marked.find(vertex) != marked.end())
      continue;

    queue.push(vertex);
    marked.insert({vertex, {true, begin_at}});
  }

  if (queue.empty())
    return;
  breadthSearch(list, queue, queue.front());
}
