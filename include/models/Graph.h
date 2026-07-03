#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>
#include <vector>

#include "models/Edge.h"

class Graph
{
public:
    std::map<std::string, std::vector<std::string>> adjacencyList;

    void addNode(const std::string &id);
    void addEdge(const std::string &from, const std::string &to);
    std::vector<std::string> getNodes() const;
    std::vector<Edge> getEdges() const;
    void print() const;
};

#endif
