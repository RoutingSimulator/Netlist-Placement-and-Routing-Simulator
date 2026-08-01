#include "analyzer/GraphAnalyzer.h"

#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>

GraphAnalyzer::GraphAnalyzer(const Graph &graph) : graph(graph) {}

Analysis GraphAnalyzer::analyze(const std::string &startNode) const
{
    Analysis analysis;
    analysis.startNode = startNode;

    bfs(startNode, analysis.bfsOrder, analysis.bfsLevels);

    analysis.dfsOrder = dfs(startNode);

    return analysis;
}

Analysis GraphAnalyzer::analyzeFromFirstNode() const
{
    const auto nodes = graph.getNodes();
    if (nodes.empty())
        return Analysis{};

    return analyze(nodes.front());
}

void GraphAnalyzer::printAnalysis(const Analysis &analysis) const
{
    std::cout << "Graph analysis from node " << analysis.startNode << ":" << std::endl;

    std::cout << "BFS order: ";
    for (const auto &node : analysis.bfsOrder)
        std::cout << node << " ";
    std::cout << std::endl;

    std::cout << "DFS order: ";
    for (const auto &node : analysis.dfsOrder)
        std::cout << node << " ";
    std::cout << std::endl;

    std::cout << "BFS levels:" << std::endl;
    for (const auto &entry : analysis.bfsLevels)
        std::cout << "  " << entry.first << " -> level " << entry.second << std::endl;
}

void GraphAnalyzer::bfs(const std::string &start,
                        std::vector<std::string> &order,
                        std::map<std::string, int> &levels) const
{
    order.clear();
    levels.clear();

    std::unordered_set<std::string> visited;
    std::queue<std::string> queue;

    visited.insert(start);
    levels[start] = 0;
    queue.push(start);

    while (!queue.empty())
    {
        const std::string current = queue.front();
        queue.pop();
        order.push_back(current);

        const auto it = graph.getAdjacencyList().find(current);
        if (it == graph.getAdjacencyList().end())
            continue;

        for (const auto &neighbor : it->second)
        {
            if (visited.count(neighbor))
                continue;

            visited.insert(neighbor);
            levels[neighbor] = levels[current] + 1;
            queue.push(neighbor);
        }
    }
}

std::vector<std::string> GraphAnalyzer::dfs(const std::string &start) const
{
    std::vector<std::string> order;
    std::unordered_set<std::string> visited;
    std::stack<std::string> stack;

    stack.push(start);

    while (!stack.empty())
    {
        const std::string current = stack.top();
        stack.pop();

        if (visited.count(current))
            continue;

        visited.insert(current);
        order.push_back(current);

        const auto it = graph.getAdjacencyList().find(current);
        if (it == graph.getAdjacencyList().end())
            continue;

        for (auto neighbor = it->second.rbegin(); neighbor != it->second.rend(); ++neighbor)
        {
            if (!visited.count(*neighbor))
                stack.push(*neighbor);
        }
    }

    return order;
}