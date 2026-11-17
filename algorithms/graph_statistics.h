#pragma once

#include "../structures/adj_list.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>

// Calcula estatísticas de um grafo não dirigido e conexo:
// - Excentricidade (eccentricity) de cada vértice
// - Closeness centrality normalizada de cada vértice
//
// Ambas dependem apenas das distâncias de caminho mínimo (número de arestas,
// grafo sem pesos), obtidas com uma BFS a partir de cada vértice.
class GraphStatistics {
public:
  // O grafo não é copiado: precisa continuar vivo enquanto o objeto existir.
  explicit GraphStatistics(const AdjListGraph &graph);

  // Excentricidade de cada vértice.
  // Vértice inalcançável => infinito (só acontece se o grafo for desconexo).
  std::map<uint16_t, double> eccentricities() const;

  // Closeness centrality normalizada de cada vértice.
  std::map<uint16_t, double> closenessCentralities() const;

  // Betweeness centrality
  std::map<uint16_t, double> betweenessCentralities() const;
  std::map<uint16_t, double>
  normalizeBC(std::map<uint16_t, double> bcMap) const;

  // Escrevem um vértice por linha, no formato "<id>: <valor>".
  // Retornam false se não conseguirem abrir o arquivo.
  bool writeEccentricity(const std::string &path) const;
  bool writeClosenessCentrality(const std::string &path) const;
  bool writeBetweenessCentrality(const std::string &path) const;

private:
  const AdjListGraph &graph_;

  // BFS a partir de `source`: distância (em arestas) até cada vértice
  // alcançável. Vértices inalcançáveis não aparecem no mapa.
  std::map<uint16_t, std::size_t> bfsDistances(uint16_t source) const;
  // Mesma coisa que o de cima só que retornando o caminho percorrido
  std::map<uint16_t, std::vector<std::vector<uint16_t>>>
  bfsPaths(uint16_t source) const;

  // Calcula os números de menor caminho entre todos os nós no grafo
  std::map<std::pair<uint16_t, uint16_t>, std::vector<std::vector<uint16_t>>>
  calculateAllShortestPaths() const;

  // Retorna o número de menores distâncias que passam por um nó
  double getDistancesThroughV(
      const std::map<std::pair<uint16_t, uint16_t>,
                     std::vector<std::vector<uint16_t>>> &distances,
      uint16_t v) const;

  // max e min para os maps
  double mapMax(std::map<uint16_t, double> map) const;
  double mapMin(std::map<uint16_t, double> map) const;
};
