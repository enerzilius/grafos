#include "graph_statistics.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <limits>
#include <queue>

GraphStatistics::GraphStatistics(const AdjListGraph &graph) : graph_(graph) {}

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

// Excentricidade (eccentricity)
// A excentricidade de um vértice v é a maior distância de caminho mínimo entre
// v e qualquer outro vértice do grafo:  ecc(v) = max_u d(v, u).
// Ela mede o quão "longe" v está do vértice mais distante dele. Quanto menor a
// excentricidade, mais central é o vértice (ele alcança todos em poucos
// passos). O menor valor de excentricidade do grafo é o raio, e o maior é o
// diâmetro.
// Ref: https://www.baeldung.com/cs/graphs-eccentricity-radius-diameter-center-periphery
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
