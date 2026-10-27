#include "algorithms/graph_statistics.h"
#include "structures/adj_list.h"
#include <iostream>

int main() {
  AdjListGraph graph(true);

  // O segundo argumento (true) é o que realmente marca o grafo como não
  // dirigido: readFromGEXFFile sobrescreve a flag passada no construtor.
  graph.readFromGEXFFile("data/LesMiserables.gexf", true);

  if (graph.list.empty()) {
    std::cout << "Grafo vazio, nada a calcular.\n";
    return 1;
  }
  std::cout << "Vertices lidos: " << graph.list.size() << "\n";

  GraphStatistics stats(graph);

  if (!stats.writeEccentricity("eccentricity.txt") ||
      !stats.writeClosenessCentrality("closeness_centrality.txt")) {
    std::cout << "Erro ao escrever os arquivos de saida.\n";
    return 1;
  }

  std::cout << "Gerados: eccentricity.txt e closeness_centrality.txt\n";
  return 0;
}
