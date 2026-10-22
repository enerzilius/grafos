#include "algorithms/search.h"
#include "structures/adj_list.h"
#include <iostream>

int main() {
  AdjListGraph graph(true);

  // graph.readFromGEXFFile("data/teste_gexf.gexf");
  graph.readFromTextFile("data/teste_cc.txt");
  graph.print();

  uint16_t node = 0;
  auto cC_1 = gsa::closenessCentrality(graph.list, node);
  node = 3;
  auto cC_2 = gsa::closenessCentrality(graph.list, node);

  std::cout<<"Closeness centrality of node [0] = "<<cC_1<<"\n";
  std::cout<<"Closeness centrality of node [3] = "<<cC_2<<"\n";

  exit(0);
}
