#include "algorithms/search.h"
#include "structures/adj_list.h"

int main() {
  AdjListGraph graph(true);

  graph.readFromFile("data/1a.txt");
  graph.print();

  SearchAlgorithms().depthFirstSearch(graph.list, 0);

  graph.readFromFile("data/1b.txt");
  graph.print();

  SearchAlgorithms().breadthFirstSearch(graph.list, 0);
  exit(0);
}
