#include "algorithms/search.h"
#include "structures/adj_list.h"

int main() {
  AdjListGraph graph(true);

  graph.readFromFile("data/1a.txt");
  graph.print();

  gsa::depthFirstSearch(graph.list, 0);

  graph.readFromFile("data/1b.txt");
  graph.print();

  gsa::breadthFirstSearch(graph.list, 0);

  graph.readFromFile("data/1c.txt");
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

  graph.clearGraph();
  graph.readFromFile("data/2a.txt");
  graph.print();

  gsa::precedenceScheduling(graph.list);

  exit(0);
}
