#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <string>

class Graph {
public:
    std::map<std::string, std::vector<std::string>> adjacencyList;

    void addEdge(std::string from, std::string to);
    void print();
};

#endif
