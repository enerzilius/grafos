#include "algorithms/search.h"
#include "structures/adj_list.h"

int main() {
  AdjListGraph graph(true);

  graph.readFromTextFile("data/1a.txt");
  graph.print();

  gsa::depthFirstSearch(graph.list, 0);

  graph.readFromTextFile("data/1b.txt");
  graph.print();

  gsa::breadthFirstSearch(graph.list, 0);

  graph.readFromTextFile("data/1c.txt");
  graph.print();

  gsa::searchConnectedComponents(graph.list);

  graph.clearGraph();
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 1);
  graph.addEdge(1, 3);
  graph.addEdge(2, 3);
  graph.addEdge(3, 1);
  graph.print();
  graph.reverseGraph();
  graph.print();

  gsa::precedenceScheduling(graph.list);

  graph.clearGraph();
  graph.readFromTextFile("data/2a.txt");
  graph.print();

  graph.readFromGEXFFile("data/teste_gexf.gexf");
  graph.print();



  exit(0);
}
