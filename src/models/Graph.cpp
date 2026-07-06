#include "models/Graph.h"

#include <iostream>
#include <set>
#include <utility>

void Graph::addNode(const std::string &id)
{
    adjacencyList[id];
}

void Graph::addEdge(const std::string &from, const std::string &to)
{
    addNode(from);
    addNode(to);
    adjacencyList[from].push_back(to);
    adjacencyList[to].push_back(from);
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

std::vector<Edge> Graph::getEdges() const
{
    std::vector<Edge> edges;
    std::set<std::pair<std::string, std::string>> seen;

    for (const auto &entry : adjacencyList)
    {
        for (const auto &to : entry.second)
        {
            const auto key = entry.first < to
                ? std::make_pair(entry.first, to)
                : std::make_pair(to, entry.first);

            if (seen.insert(key).second)
                edges.push_back({entry.first, to});
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

        std::cout << std::endl;
    }
}
