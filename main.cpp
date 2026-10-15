#include "algorithms/search.h"
#include "structures/adj_list.h"
#include <iostream>

int main() {
  AdjListGraph graph(true);
  
  graph.readFromGEXFFile("data/teste_gexf.gexf");
  graph.print();

  exit(0);
}
