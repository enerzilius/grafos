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

static void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                        const uint16_t beginAt);
static void breadthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          std::queue<uint16_t> &queue, const uint16_t beginAt);
static void
connectedComponents(const std::map<uint16_t, std::vector<uint16_t>> &list,
                    std::map<uint16_t, uint16_t> &components,
                    uint16_t componentId, const uint16_t beginAt);
static uint16_t
getUnmarked(const std::map<uint16_t, std::vector<uint16_t>> &list,
            const uint16_t beginAt);
static void printTable();
static void
printConnectedComponents(const std::map<uint16_t, uint16_t> &components);

void gsa::depthFirstSearch(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    const uint16_t beginAt) {
  marked.clear();
  marked.insert({beginAt, {true, beginAt}});
  depthSearch(list, beginAt);
  printTable();
}

static void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                        const uint16_t beginAt = 0) {

  std::vector<uint16_t> currentVector = list.at(beginAt);
  if (currentVector.empty())
    return;

  for (const uint16_t vertex : currentVector) {
    if (marked.find(vertex) != marked.end())
      continue;
    marked.insert({vertex, {true, beginAt}});

    depthSearch(list, vertex);
  }
}

void gsa::breadthFirstSearch(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    const uint16_t beginAt) {
  std::queue<uint16_t> queue;
  marked.clear();
  queue.push(beginAt);
  marked.insert({beginAt, {true, beginAt}});
  breadthSearch(list, queue, beginAt);
  printTable();
}

static void breadthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          std::queue<uint16_t> &queue,
                          const uint16_t beginAt = 0) {

  std::vector<uint16_t> currentVector = list.at(beginAt);

  if (currentVector.empty() || queue.empty())
    return;

  queue.pop();

  for (const uint16_t vertex : currentVector) {
    if (marked.find(vertex) != marked.end())
      continue;

    queue.push(vertex);
    marked.insert({vertex, {true, beginAt}});
  }

  if (queue.empty())
    return;
  breadthSearch(list, queue, queue.front());
}

void gsa::searchConnectedComponents(
    const std::map<uint16_t, std::vector<uint16_t>> &list, uint16_t beginAt) {
  marked.clear();

  std::map<uint16_t, uint16_t> components;
  uint16_t componentId = 0;
  bool checkedAll = false;

  marked.insert({beginAt, {true, beginAt}});
  while (!checkedAll) {
    connectedComponents(list, components, componentId, beginAt);

    uint16_t checkNode = getUnmarked(list, beginAt);
    if (checkNode == beginAt)
      checkedAll = true;
    else {
      beginAt = checkNode;
      componentId++;
    }
  }
  printConnectedComponents(components);
}

static void
connectedComponents(const std::map<uint16_t, std::vector<uint16_t>> &list,
                    std::map<uint16_t, uint16_t> &components,
                    uint16_t componentId, const uint16_t beginAt) {
  std::vector<uint16_t> currentVector = list.at(beginAt);
  components.insert({beginAt, componentId});
  if (currentVector.empty())
    return;

  for (const uint16_t vertex : currentVector) {
    if (marked.find(vertex) != marked.end())
      continue;
    marked.insert({vertex, {true, beginAt}});

    connectedComponents(list, components, componentId, vertex);
  }
}

static uint16_t
getUnmarked(const std::map<uint16_t, std::vector<uint16_t>> &list,
            uint16_t beginAt) {
  for (auto const &[key, value] : list) {
    if (marked.find(key) == marked.end())
      return key;
  }
  return beginAt; // sentinel: nothing left unmarked
}

static void printTable() {
  std::cout << "\nv | marked | edgeTo \n";
  for (auto const &[key, value] : marked) {
    std::cout << key << " | " << (value.marked ? "T" : "F") << " | "
              << value.edgeTo << "\n";
  }
  std::cout << "\n";
}

static void printConnectedComponents(
    const std::map<uint16_t, uint16_t> &connectedComponents) {
  std::cout << "\nv | componentId\n";
  for (auto const &[key, value] : connectedComponents) {
    std::cout << key << " | " << value << "\n";
  }
  std::cout << "\n";
}
