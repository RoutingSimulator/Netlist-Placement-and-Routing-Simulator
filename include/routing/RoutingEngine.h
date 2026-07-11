#ifndef ROUTING_ENGINE_H
#define ROUTING_ENGINE_H

#include <vector>

#include "models/Graph.h"
#include "models/Route.h"
#include "placement/PlacementEngine.h"

class RoutingEngine
{
public:
    RoutingEngine(const Graph &graph, const PlacementEngine &placement);

    void routeConnections();
    void printRoutes() const;
    const std::vector<Route> &getRoutes() const;

private:
    const Graph &graph;
    const PlacementEngine &placement;
    std::vector<Route> routes;

    Route routeEdge(const std::string &from, const std::string &to) const;
};

#endif
