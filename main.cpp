#include "structures/adj_list.h"
#include <iostream>
#include <cstdlib>

int main() {
    AdjListGraph graph(true);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.print();

    graph.readFromFile("data/1a.txt");
    graph.print();

    exit(0);
}