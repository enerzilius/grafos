#include "search.h"

#include <iostream>
#include <stack>
#include <algorithm>

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
static void stronglyConnectedComponents(const std::map<uint16_t, std::vector<uint16_t>> &list,
                    std::map<uint16_t, uint16_t> &components,
                    uint16_t componentId, const uint16_t beginAt);
static uint16_t
getUnmarked(const std::map<uint16_t, std::vector<uint16_t>> &list,
            const uint16_t beginAt);
static void schedule(const std::map<uint16_t, std::vector<uint16_t>> &list,
                     std::stack<uint16_t> &postorder, uint16_t beginAt);

static void printTable();
static void
printConnectedComponents(const std::map<uint16_t, uint16_t> &components);
static void printStack(std::stack<uint16_t> &stack);

void gsa::depthFirstSearch(
    const std::map<uint16_t, std::vector<uint16_t>> &list,
    const uint16_t beginAt) {
  marked.clear();
  marked.insert({beginAt, {true, beginAt}});
  depthSearch(list, beginAt);
  printTable();
}

static void depthSearch(const std::map<uint16_t, std::vector<uint16_t>> &list,
                        const uint16_t beginAt) {

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
                          std::queue<uint16_t> &queue, const uint16_t beginAt) {

  std::vector<uint16_t> currentVector = list.at(beginAt);

  // if (currentVector.empty() || queue.empty())
  //   return;

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

std::vector<uint16_t> gsa::shortestPath(const std::map<uint16_t, std::vector<uint16_t>> &list, uint16_t from, uint16_t to) {
  std::map<uint16_t, uint16_t> parent;
  std::queue<uint16_t> queue;

  parent[from] = from;
  queue.push(from);

  while (!queue.empty()) {
    const uint16_t current = queue.front();
    queue.pop();

    if (current == to)
      break;

    const auto it = list.find(current);
    if (it == list.end())
      continue;

    for (const uint16_t neighbor : it->second) {
      if (parent.count(neighbor))
        continue;
      parent[neighbor] = current;
      queue.push(neighbor);
    }
  }
  if (!parent.count(to))
    return std::vector<uint16_t>{};

  std::vector<uint16_t> path;
  for (uint16_t v = to; v != from; v = parent[v])
    path.push_back(v);
  path.push_back(from);
  std::reverse(path.begin(), path.end());
  return path;
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
  return beginAt;
}

static void printTable() {
  std::cout<<"\nSEARCH'S RESULTING TABLE\n";
  std::cout << "v | marked | edgeTo \n";
  for (auto const &[key, value] : marked) {
    std::cout << key << " | " << (value.marked ? "T" : "F") << " | "
              << value.edgeTo << "\n";
  }
  std::cout << "\n";
}

static void printConnectedComponents(
    const std::map<uint16_t, uint16_t> &connectedComponents) {
  std::cout<<"\nCONNECTED COMPONENTS\n";
  std::cout << "v | componentId\n";
  for (auto const &[key, value] : connectedComponents) {
    std::cout << key << " | " << value << "\n";
  }
  std::cout << "\n";
}

void gsa::precedenceScheduling(const std::map<uint16_t, std::vector<uint16_t>> &list,
                          std::stack<uint16_t>& returnStack, uint16_t beginAt) {
  std::stack<uint16_t> postorder;
  
  marked.clear();
  marked.insert({beginAt, {true, beginAt}});
  schedule(list, postorder, beginAt);
  //printStack(postorder);
  returnStack = std::move(postorder);
}

void gsa::precedenceScheduling(
    const std::map<uint16_t, std::vector<uint16_t>> &list, uint16_t beginAt) {
  std::stack<uint16_t> postorder;

  marked.clear();
  marked.insert({beginAt, {true, beginAt}});
  schedule(list, postorder, beginAt);
  printStack(postorder);
}

static void schedule(const std::map<uint16_t, std::vector<uint16_t>> &list,
                     std::stack<uint16_t> &postorder, uint16_t beginAt) {
  std::vector<uint16_t> currentVector = list.at(beginAt);
  if (currentVector.empty()) {
    postorder.push(beginAt);
    return;
  }

  for (const uint16_t vertex : currentVector) {
    if (marked.find(vertex) != marked.end())
      continue;
    marked.insert({vertex, {true, beginAt}});

    schedule(list, postorder, vertex);
  }
  postorder.push(beginAt);
}

static void printStack(std::stack<uint16_t> &stack) {
  std::cout << "\nPRECENDE SCHEDULING'S REVERSE POSTORDER: \n";
  while (!stack.empty()) {
    std::cout << stack.top() << " ";
    stack.pop();
  }
  std::cout<<"\n";
}

void gsa::kosarajuShahirSCC(
    const AdjListGraph& graph) {
  if(graph.isUndirected) {
    std::cout<<"[!] Graph is undirected, searching for connected components.\n";
    gsa::searchConnectedComponents(graph.list, 0);
    return;
  }

  // Kosaraju-Shahir

  // Phase 1
  AdjListGraph reversed = graph;
  reversed.reverseGraph();

  std::stack<uint16_t> postorder;
  gsa::precedenceScheduling(reversed.list, postorder);

  // Phase 2
  marked.clear();
  std::map<uint16_t, uint16_t> components;
  uint16_t componentId = 0;
  bool checkedAll = false;

  uint16_t beginAt =  postorder.top();
  marked.insert({beginAt, {true, beginAt}});

  while (!postorder.empty()) {
    stronglyConnectedComponents(graph.list, components, componentId, beginAt);

    postorder.pop();
    componentId++;
    beginAt = postorder.top();
  }
  printConnectedComponents(components);
}

static void stronglyConnectedComponents(const std::map<uint16_t, std::vector<uint16_t>> &list,
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

    stronglyConnectedComponents(list, components, componentId, vertex);
  }
}

void gsa::lazyPrimMST(const std::map<uint16_t, std::vector<uint16_t>> &list, uint16_t begin_at) {
  // precisa de uma fila de prioridade

  // começa no vértice 0 e adiciona todas as arestas dele em uma fila de prioridade ordenada pelo peso

  // adiciona a aresta com menor peso pra árvore (se ela não conecta aos vertices que já estão na árvore)
  // remove a aresta adicionada na lista
  // adiciona as arestas conectadas ao novo vértice da árvore à lista de prioridade (tem que manter ordenada) 
  // repete pro próximo vértice

  // repete até v-1
} 

double gsa::closenessCentrality(std::map<uint16_t, std::vector<uint16_t>> &list, uint16_t node) {
  double distanceSum = 0.0;

  std::map<uint16_t, std::vector<uint16_t>>::iterator it;
  for (it = list.begin(); it != list.end(); it++) {
    if(it->first == node) continue;
    distanceSum += shortestPath(list, node, it->first).size() * 1.0;
  }

  int N = list.size();
  return (N-1)/distanceSum;
}
