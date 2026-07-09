#include "placement/PlacementEngine.h"

#include <algorithm>
#include <queue>
#include <set>

PlacementEngine::PlacementEngine(Graph &graph) : graph(graph) {}

void PlacementEngine::placeComponents()
{
    locations.clear();
    spanningTree.clear();

    const std::vector<std::string> nodes = graph.getNodes();
    if (nodes.empty())
        return;

    if (nodes.size() == 1)
    {
        locations[nodes.front()] = {0, 0};
        return;
    }

    const std::string root = selectRootNode();
    const std::map<std::string, int> layers = computeLayers(root);
    placeByLayers(layers);
}

std::string PlacementEngine::selectRootNode() const
{
    const std::vector<std::string> nodes = graph.getNodes();
    return nodes.front();
}

std::map<std::string, std::vector<std::string>> PlacementEngine::buildUndirectedAdjacency() const
{
    std::map<std::string, std::set<std::string>> neighborSets;

    for (const auto &entry : graph.adjacencyList)
    {
        neighborSets[entry.first];
        for (const auto &neighbor : entry.second)
        {
            neighborSets[entry.first].insert(neighbor);
            neighborSets[neighbor].insert(entry.first);
        }
    }

    std::map<std::string, std::vector<std::string>> undirected;
    for (const auto &entry : neighborSets)
        undirected[entry.first] = {entry.second.begin(), entry.second.end()};

    return undirected;
}

std::map<std::string, int> PlacementEngine::computeLayers(const std::string &root)
{
    const auto undirected = buildUndirectedAdjacency();
    std::map<std::string, int> layers;
    std::set<std::string> visited;
    int nextComponentBase = 0;

    auto bfsFrom = [&](const std::string &startNode)
    {
        std::queue<std::string> queue;
        visited.insert(startNode);
        layers[startNode] = nextComponentBase;
        queue.push(startNode);

        while (!queue.empty())
        {
            const std::string current = queue.front();
            queue.pop();

            const auto adjacencyIt = undirected.find(current);
            if (adjacencyIt == undirected.end())
                continue;

            for (const auto &neighbor : adjacencyIt->second)
            {
                if (visited.count(neighbor))
                    continue;

                visited.insert(neighbor);
                layers[neighbor] = layers[current] + 1;
                spanningTree.push_back({current, neighbor});
                queue.push(neighbor);
            }
        }

        int maxLayer = nextComponentBase;
        for (const auto &entry : layers)
            maxLayer = std::max(maxLayer, entry.second);

        nextComponentBase = maxLayer + 1;
    };

    bfsFrom(root);

    for (const auto &node : graph.getNodes())
    {
        if (!visited.count(node))
            bfsFrom(node);
    }

    return layers;
}

void PlacementEngine::placeByLayers(const std::map<std::string, int> &layers)
{
    std::map<int, std::vector<std::string>> nodesByLayer;

    for (const auto &entry : layers)
        nodesByLayer[entry.second].push_back(entry.first);

    for (auto &entry : nodesByLayer)
    {
        std::sort(entry.second.begin(), entry.second.end());

        const int level = entry.first;
        const int x = level * gridUnit;

        for (size_t i = 0; i < entry.second.size(); ++i)
        {
            const int y = static_cast<int>(i) * gridUnit;
            locations[entry.second[i]] = {x, y};
        }
    }
}
