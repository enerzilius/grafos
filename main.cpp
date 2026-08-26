#include "algorithms/search.h"
#include "structures/adj_list.h"
#include <cstdlib>

int main() {
  AdjListGraph graph(true);

  graph.readFromFile("data/1a.txt");
  graph.print();

  depthFirstSearch(graph.list, 0);

  exit(0);
}
