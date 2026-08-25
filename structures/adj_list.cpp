#include "adj_list.h"
#include <cstdlib>
#include <cstdint>
#include <vector>

void AdjListGraph::addEdge(const uint16_t vertex, uint16_t adjacentVertex) {
    list[vertex].push_back(adjacentVertex);
    list[adjacentVertex].push_back(vertex);
}

//void removeEdge(const uint16_t vertex, uint16_t adjacentVertex);
void readFromFile(const std::string& path);
void AdjListGraph::print() {
    // for (const std::vertex<uint16_t> )
    // {
    //     /* code */
    // }
    
// }