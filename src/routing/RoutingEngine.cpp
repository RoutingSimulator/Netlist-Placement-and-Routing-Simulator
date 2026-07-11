#include "routing/RoutingEngine.h"

#include <cmath>
#include <iostream>

RoutingEngine::RoutingEngine(const Graph &graph, const PlacementEngine &placement)
    : graph(graph), placement(placement)
{
}

const std::vector<Route> &RoutingEngine::getRoutes() const
{
    return routes;
}

void RoutingEngine::routeConnections()
{
    routes.clear();

    for (const auto &edge : graph.getEdges())
        routes.push_back(routeEdge(edge.from, edge.to));
}

void RoutingEngine::printRoutes() const
{
    std::cout << "Routes:" << std::endl;

    for (const auto &route : routes)
    {
        std::cout << route.from << " -> " << route.to << ": ";

        for (size_t i = 0; i < route.waypoints.size(); ++i)
        {
            const Position &point = route.waypoints[i];
            std::cout << "(" << point.x << ", " << point.y << ")";

            if (i + 1 < route.waypoints.size())
                std::cout << " -> ";
        }

        std::cout << std::endl;
    }
}

Route RoutingEngine::routeEdge(const std::string &from, const std::string &to) const
{
    Route route;
    route.from = from;
    route.to = to;

    const Position start = placement.getLocations().at(from);
    const Position end = placement.getLocations().at(to);

    route.waypoints.push_back(start);

    if (start.x == end.x || start.y == end.y)
    {
        route.waypoints.push_back(end);
        return route;
    }

    const Position horizontalFirst = {end.x, start.y};

    route.waypoints.push_back(horizontalFirst);
    route.waypoints.push_back(end);
    return route;
}
