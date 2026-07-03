#include "analyzer/GraphAnalyzer.h"

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>

GraphAnalyzer::GraphAnalyzer(Graph &graph) : graph(graph) {}

Analysis GraphAnalyzer::analyze(const std::string &startNode)
{
    Analysis analysis;
    analysis.startNode = startNode;
    analysis.bfsOrder = bfs(startNode);
    analysis.dfsOrder = dfs(startNode);

    std::map<std::string, bool> visited;
    std::queue<std::string> queue;

    visited[startNode] = true;
    queue.push(startNode);
    analysis.bfsLevels[startNode] = 0;

    while (!queue.empty())
    {
        const std::string current = queue.front();
        queue.pop();

        const auto it = graph.adjacencyList.find(current);
        if (it == graph.adjacencyList.end())
            continue;

        for (const auto &neighbor : it->second)
        {
            if (visited[neighbor])
                continue;

            visited[neighbor] = true;
            analysis.bfsLevels[neighbor] = analysis.bfsLevels[current] + 1;
            queue.push(neighbor);
        }
    }

    return analysis;
}

Analysis GraphAnalyzer::analyzeFromFirstNode()
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

std::vector<std::string> GraphAnalyzer::bfs(const std::string &start)
{
    std::vector<std::string> order;
    std::map<std::string, bool> visited;
    std::queue<std::string> queue;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty())
    {
        const std::string current = queue.front();
        queue.pop();
        order.push_back(current);

        const auto it = graph.adjacencyList.find(current);
        if (it == graph.adjacencyList.end())
            continue;

        for (const auto &neighbor : it->second)
        {
            if (visited[neighbor])
                continue;

            visited[neighbor] = true;
            queue.push(neighbor);
        }
    }

    return order;
}

std::vector<std::string> GraphAnalyzer::dfs(const std::string &start)
{
    std::vector<std::string> order;
    std::set<std::string> visited;
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

        const auto it = graph.adjacencyList.find(current);
        if (it == graph.adjacencyList.end())
            continue;

        for (auto neighbor = it->second.rbegin(); neighbor != it->second.rend(); ++neighbor)
        {
            if (!visited.count(*neighbor))
                stack.push(*neighbor);
        }
    }

    return order;
}
