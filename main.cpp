#include "algorithms/search.h"
#include "structures/adj_list.h"

int main() {
  AdjListGraph graph(true);

  graph.readFromGEXFFile("./data/LesMiserables.gexf");
  graph.print();



  exit(0);
}
