#include "algorithms/search.h"
#include "structures/weighted_graph.h"

int main() {
  WeightedGraph graph(false);

  graph.readFromTextFile("./data/cmgdap.txt");
  // graph.print();

  gsa::precedenceScheduling(graph.list);

  gsa::dijkstraShortestPath(graph.list);

  return 0;
}
