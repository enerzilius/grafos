#include "algorithms/search.h"
#include "structures/weighted_graph.h"
#include <iostream>

int main() {
  WeightedGraph graph(false);

  graph.readFromTextFile("./data/teste_dijkstra.txt");
  graph.print();

  gsa::dijkstraShortestPath(graph.list);

  return 0;
}
