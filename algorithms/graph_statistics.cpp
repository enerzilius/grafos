#include "graph_statistics.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <limits>
#include <queue>

GraphStatistics::GraphStatistics(const AdjListGraph &graph) : graph_(graph) {}

double GraphStatistics::mapMax(std::map<uint16_t, double> map) const {
  if (map.empty())
    return 0.0;
  double max = map[0];

  for (const auto &[key, value] : map) {
    if (value > max)
      max = value;
  }

  return max;
}

double GraphStatistics::mapMin(std::map<uint16_t, double> map) const {
  if (map.empty())
    return 0.0;
  double min = map[0];

  for (const auto &[key, value] : map) {
    if (value < min)
      min = value;
  }

  return min;
}

std::map<uint16_t, std::size_t>
GraphStatistics::bfsDistances(uint16_t source) const {
  std::map<uint16_t, std::size_t> distances;
  std::queue<uint16_t> queue;

  distances[source] = 0;
  queue.push(source);

  while (!queue.empty()) {
    const uint16_t current = queue.front();
    queue.pop();

    const auto adjacent = graph_.list.find(current);
    if (adjacent == graph_.list.end())
      continue;

    for (const uint16_t neighbor : adjacent->second) {
      if (distances.count(neighbor))
        continue; // já visitado: a primeira visita na BFS é a menor distância
      distances[neighbor] = distances[current] + 1;
      queue.push(neighbor);
    }
  }
  return distances;
}

std::map<uint16_t, std::vector<std::vector<uint16_t>>>
GraphStatistics::bfsPaths(uint16_t source) const {
  std::map<uint16_t, std::vector<std::vector<uint16_t>>> paths;
  std::map<uint16_t, size_t> dist;
  std::queue<uint16_t> queue;

  paths[source] = {{source}};
  dist[source] = 0;
  queue.push(source);

  while (!queue.empty()) {
    const uint16_t current = queue.front();
    queue.pop();

    const auto adjacent = graph_.list.find(current);
    if (adjacent == graph_.list.end())
      continue;

    for (const uint16_t neighbor : adjacent->second) {
      // First time we see this vertex: it's on the next BFS level.
      if (!dist.count(neighbor)) {
        dist[neighbor] = dist[current] + 1;
        queue.push(neighbor);
      }

      // Only extend along edges that stay on a shortest path.
      if (dist[neighbor] == dist[current] + 1) {
        for (const auto &p : paths[current]) {
          std::vector<uint16_t> path = p;
          path.push_back(neighbor);
          paths[neighbor].push_back(std::move(path));
        }
      }
    }
  }
  return paths;
}

// Excentricidade (eccentricity)
// A excentricidade de um vértice v é a maior distância de caminho mínimo entre
// v e qualquer outro vértice do grafo:  ecc(v) = max_u d(v, u).
// Ela mede o quão "longe" v está do vértice mais distante dele. Quanto menor a
// excentricidade, mais central é o vértice (ele alcança todos em poucos
// passos). O menor valor de excentricidade do grafo é o raio, e o maior é o
// diâmetro.
// Ref:
// https://www.baeldung.com/cs/graphs-eccentricity-radius-diameter-center-periphery
std::map<uint16_t, double> GraphStatistics::eccentricities() const {
  std::map<uint16_t, double> result;

  for (const auto &[vertex, adjacent] : graph_.list) {
    const auto distances = bfsDistances(vertex);

    // Se algum vértice não foi alcançado, o grafo é desconexo e a
    // excentricidade é infinita.
    if (distances.size() != graph_.list.size()) {
      result[vertex] = std::numeric_limits<double>::infinity();
      continue;
    }

    std::size_t eccentricity = 0;
    for (const auto &[other, distance] : distances)
      eccentricity = std::max(eccentricity, distance);
    result[vertex] = static_cast<double>(eccentricity);
  }
  return result;
}

// Closeness Centrality Normalizada
// A closeness centrality indica o quão próximo um vértice está, em média, de
// todos os outros. A versão básica é o inverso da soma das distâncias de v
// até os demais vértices:  C(v) = 1 / sum_u d(v, u).
// A versão normalizada multiplica por (N - 1), onde N é o número de vértices:
//   C_norm(v) = (N - 1) / sum_u d(v, u)
// que equivale ao inverso da distância média de v até os outros vértices.
// O resultado fica entre 0 e 1 (1 = v é vizinho direto de todos os outros);
// quanto maior o valor, mais central é o vértice na rede. A normalização
// permite comparar grafos de tamanhos diferentes.
// Pré-requisito: grafo conexo (todas as distâncias são finitas).
std::map<uint16_t, double> GraphStatistics::closenessCentralities() const {
  std::map<uint16_t, double> result;
  const double n = static_cast<double>(graph_.list.size());

  for (const auto &[vertex, adjacent] : graph_.list) {
    const auto distances = bfsDistances(vertex);

    double distanceSum = 0.0;
    for (const auto &[other, distance] : distances)
      distanceSum += static_cast<double>(distance);

    // distanceSum == 0 só ocorre em grafo de 1 vértice (ou vértice isolado).
    result[vertex] = distanceSum > 0.0 ? (n - 1.0) / distanceSum : 0.0;
  }
  return result;
}

// Calcula e armazena os menores caminhos para todos os pares de nós
std::map<std::pair<uint16_t, uint16_t>, std::vector<std::vector<uint16_t>>>
GraphStatistics::calculateAllShortestPaths() const {
  std::map<std::pair<uint16_t, uint16_t>, std::vector<std::vector<uint16_t>>>
      result;

  for (const auto &[v, list] : graph_.list) {
    auto paths = bfsPaths(v); // non-const so the move really moves
    for (auto &[u, pathList] : paths) {
      if (v == u)
        continue;
      result[{v, u}] = std::move(pathList);
    }
  }

  return result;
}

// Descobre o número de menores distâncias que passam por um nó
double GraphStatistics::getDistancesThroughV(
    const std::map<std::pair<uint16_t, uint16_t>,
                   std::vector<std::vector<uint16_t>>> &distances,
    uint16_t v) const {
  double total = 0.0;

  for (const auto &[pair, pathList] : distances) {
    if (pair.first == v || pair.second == v)
      continue;

    size_t through = 0;
    for (const auto &path : pathList) {
      if (std::find(path.begin(), path.end(), v) != path.end())
        through++;
    }
    total += static_cast<double>(through) / pathList.size();
  }

  return total;
}

// Betweeness Centrality
// Essa medida indica o quão frequente o nó analisado está nos menores caminhos
// de pares de vértices no grafo. O cálculo é feito fazendo o somatório da
// divisão do número de menores caminhos entre dois nós que passa pelo vértice
// analisado pelo menores caminhos entre esses nós, para cada nó:
// betweeness_centrality(v) = sum(sigma_stv/sigma_st)
// onde s != v != t, v é o nó em questão, sigma_st é o número de menores
// caminhos de um nó s a um t e sigma_stv e o número de menores caminhos de s
// a t que passam por v.
std::map<uint16_t, double> GraphStatistics::betweenessCentralities() const {
  std::map<uint16_t, double> result;

  const auto distances = calculateAllShortestPaths();
  const double n = static_cast<double>(graph_.list.size());
  const double norm = (n > 2) ? (n - 1) * (n - 2) : 1.0;

  for (const auto &[vertex, adjacent] : graph_.list) {
    const double sum = getDistancesThroughV(distances, vertex);
    result[vertex] = distances.empty() ? 0.0 : sum / norm;
  }
  return result;
}

bool GraphStatistics::writeEccentricity(const std::string &path) const {
  std::ofstream file(path);
  if (!file)
    return false;

  for (const auto &[vertex, value] : eccentricities()) {
    file << vertex << ": ";
    if (value == std::numeric_limits<double>::infinity())
      file << "infinito\n";
    else
      file << static_cast<std::size_t>(value) << "\n";
  }
  return true;
}

bool GraphStatistics::writeClosenessCentrality(const std::string &path) const {
  std::ofstream file(path);
  if (!file)
    return false;

  file << std::fixed << std::setprecision(6);
  for (const auto &[vertex, value] : closenessCentralities())
    file << vertex << ": " << value << "\n";
  return true;
}

bool GraphStatistics::writeBetweenessCentrality(const std::string &path) const {
  std::ofstream file(path);
  if (!file)
    return false;

  std::map<uint16_t, double> bcMap = betweenessCentralities();
  // bcMap = normalizeBC(bcMap);

  file << std::fixed << std::setprecision(6);
  for (const auto &[vertex, value] : bcMap)
    file << vertex << ": " << value << "\n";
  return true;
}
