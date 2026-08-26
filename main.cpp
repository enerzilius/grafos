#include "structures/adj_list.h"
#include <iostream>
#include <cstdlib>

int main() {
    AdjListGraph graph(true);

    graph.readFromFile("data/1a.txt");
    graph.print();

    exit(0);
}