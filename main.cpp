#include "algorithms/search.h"
#include "structures/adj_list.h"
#include <iostream>

int main() {
  AdjListGraph graph(true);

  graph.readFromGEXFFile("data/teste_gexf.gexf");
  graph.print();

  uint16_t node = 0;
  auto cC = gsa::closenessCentrality(graph.list, node);
  std::cout<<"Closeness centrality of node ["<<node<<"] = "<<cC<<"\n";

  exit(0);
}
