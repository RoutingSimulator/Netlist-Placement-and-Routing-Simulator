#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>
#include <vector>

#include "models/Edge.h"

class Graph
{
public:
    void addNode(const std::string &id);
    void addEdge(const std::string &from, const std::string &to);
    std::vector<std::string> getNodes() const;
    std::vector<Edge> getEdges() const;
    const std::map<std::string, std::vector<std::string>> &getAdjacencyList() const;
    void print() const;

private:
    std::map<std::string, std::vector<std::string>> adjacencyList;
};

#endif
