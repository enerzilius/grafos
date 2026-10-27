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

  // Escrevem um vértice por linha, no formato "<id>: <valor>".
  // Retornam false se não conseguirem abrir o arquivo.
  bool writeEccentricity(const std::string &path) const;
  bool writeClosenessCentrality(const std::string &path) const;

private:
  const AdjListGraph &graph_;

  // BFS a partir de `source`: distância (em arestas) até cada vértice
  // alcançável. Vértices inalcançáveis não aparecem no mapa.
  std::map<uint16_t, std::size_t> bfsDistances(uint16_t source) const;
};
