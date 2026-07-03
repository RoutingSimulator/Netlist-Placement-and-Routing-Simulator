#include "placement/PlacementEngine.h"

#include <algorithm>
#include <cmath>
#include <set>

PlacementEngine::PlacementEngine(Graph &graph) : graph(graph) {}

void PlacementEngine::placeComponents()
{
    const auto nodes = collectNodes();
    locations.clear();

    if (nodes.empty())
        return;

    if (nodes.size() == 1)
    {
        locations[nodes.front()] = {0, 0};
        return;
    }

    forceDirectedPlacement(nodes);
}

std::vector<std::string> PlacementEngine::collectNodes() const
{
    std::set<std::string> nodeSet;

    for (const auto &entry : graph.adjacencyList)
    {
        nodeSet.insert(entry.first);
        for (const auto &neighbor : entry.second)
            nodeSet.insert(neighbor);
    }

    return {nodeSet.begin(), nodeSet.end()};
}

void PlacementEngine::forceDirectedPlacement(const std::vector<std::string> &nodes)
{
    const int iterations = 200;
    const double repulsion = 500.0;
    const double attraction = 0.05;
    const double damping = 0.85;
    const int gridUnit = 2;

    std::map<std::string, double> posX;
    std::map<std::string, double> posY;
    std::map<std::string, double> velX;
    std::map<std::string, double> velY;

    const double radius = nodes.size() * gridUnit * 2.0;
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        const double angle = 2.0 * M_PI * static_cast<double>(i) / nodes.size();
        posX[nodes[i]] = radius * std::cos(angle);
        posY[nodes[i]] = radius * std::sin(angle);
        velX[nodes[i]] = 0.0;
        velY[nodes[i]] = 0.0;
    }

    for (int iter = 0; iter < iterations; ++iter)
    {
        std::map<std::string, double> forceX;
        std::map<std::string, double> forceY;

        for (const auto &node : nodes)
        {
            forceX[node] = 0.0;
            forceY[node] = 0.0;
        }

        for (size_t i = 0; i < nodes.size(); ++i)
        {
            for (size_t j = i + 1; j < nodes.size(); ++j)
            {
                double dx = posX[nodes[i]] - posX[nodes[j]];
                double dy = posY[nodes[i]] - posY[nodes[j]];
                double dist = std::sqrt(dx * dx + dy * dy);
                if (dist < 0.01)
                    dist = 0.01;

                const double force = repulsion / (dist * dist);
                const double fx = force * dx / dist;
                const double fy = force * dy / dist;

                forceX[nodes[i]] += fx;
                forceY[nodes[i]] += fy;
                forceX[nodes[j]] -= fx;
                forceY[nodes[j]] -= fy;
            }
        }

        for (const auto &entry : graph.adjacencyList)
        {
            const std::string &from = entry.first;
            for (const auto &to : entry.second)
            {
                double dx = posX[to] - posX[from];
                double dy = posY[to] - posY[from];
                double dist = std::sqrt(dx * dx + dy * dy);
                if (dist < 0.01)
                    dist = 0.01;

                const double force = attraction * dist;
                const double fx = force * dx / dist;
                const double fy = force * dy / dist;

                forceX[from] += fx;
                forceY[from] += fy;
                forceX[to] -= fx;
                forceY[to] -= fy;
            }
        }

        for (const auto &node : nodes)
        {
            velX[node] = (velX[node] + forceX[node]) * damping;
            velY[node] = (velY[node] + forceY[node]) * damping;
            posX[node] += velX[node];
            posY[node] += velY[node];
        }
    }

    double minX = posX[nodes.front()];
    double minY = posY[nodes.front()];
    for (const auto &node : nodes)
    {
        minX = std::min(minX, posX[node]);
        minY = std::min(minY, posY[node]);
    }

    for (const auto &node : nodes)
    {
        const int x = static_cast<int>(std::lround((posX[node] - minX) / gridUnit)) * gridUnit;
        const int y = static_cast<int>(std::lround((posY[node] - minY) / gridUnit)) * gridUnit;
        locations[node] = {x, y};
    }

    resolveOverlaps(nodes, gridUnit);
}

void PlacementEngine::resolveOverlaps(const std::vector<std::string> &nodes, int gridUnit)
{
    bool adjusted = true;
    while (adjusted)
    {
        adjusted = false;
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            for (size_t j = i + 1; j < nodes.size(); ++j)
            {
                const Position &a = locations[nodes[i]];
                const Position &b = locations[nodes[j]];

                if (a.x == b.x && a.y == b.y)
                {
                    locations[nodes[j]].x += gridUnit;
                    adjusted = true;
                }
            }
        }
    }
}
