#include "models/Graph.h"

#include <iostream>
#include <set>

void Graph::addNode(const std::string &id)
{
    adjacencyList[id];
}

void Graph::addEdge(const std::string &from, const std::string &to)
{
    addNode(from);
    addNode(to);
    adjacencyList[from].push_back(to);
}

std::vector<std::string> Graph::getNodes() const
{
    std::set<std::string> nodeSet;

    for (const auto &entry : adjacencyList)
    {
        nodeSet.insert(entry.first);
        for (const auto &neighbor : entry.second)
            nodeSet.insert(neighbor);
    }

    return {nodeSet.begin(), nodeSet.end()};
}

const std::map<std::string, std::vector<std::string>> &Graph::getAdjacencyList() const
{
    return adjacencyList;
}

std::vector<Edge> Graph::getEdges() const
{
    std::vector<Edge> edges;

    for (const auto &[from, neighbors] : adjacencyList)
    {
        for (const auto &to : neighbors)
        {
            edges.push_back({from, to});
        }
    }

    return edges;
}

void Graph::print() const
{
    for (const auto &entry : adjacencyList)
    {
        std::cout << entry.first << " : ";

        for (const auto &neighbor : entry.second)
            std::cout << neighbor << " ";

        std::cout << '\n';
    }
}