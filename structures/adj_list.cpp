#include "adj_list.h"
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <iostream>

AdjListGraph::AdjListGraph(bool undirectional = false) {
    isUndirectional = undirectional;
    list = {};
}

AdjListGraph::~AdjListGraph() {
    list = {};
}

void AdjListGraph::addEdge(const uint16_t vertex, uint16_t adjacentVertex) {
    list[vertex].push_back(adjacentVertex);
    list[adjacentVertex].push_back(vertex);
}

//void removeEdge(const uint16_t vertex, uint16_t adjacentVertex);
void readFromFile(const std::string& path);

void AdjListGraph::print() {
    std::map<uint16_t, std::vector<uint16_t>>::iterator iterator;
    for (iterator = list.begin(); iterator != list.end(); iterator++) {
        std::cout<<"\n"<<iterator->first;
        for(const uint16_t& vertex : iterator->second) {
            std::cout<<" - "<<vertex;
        }
    }
    std::cout<<"\n";    
}