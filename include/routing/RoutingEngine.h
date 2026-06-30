#ifndef ROUTING_ENGINE_H
#define ROUTING_ENGINE_H

#include <vector>

#include "models/Graph.h"
#include "models/Route.h"
#include "placement/PlacementEngine.h"

class RoutingEngine
{
public:
    std::vector<Route> routes;

    RoutingEngine(Graph &graph, PlacementEngine &placement);

    void routeConnections();
    void printRoutes() const;

private:
    Graph &graph;
    PlacementEngine &placement;

    Route routeEdge(const std::string &from, const std::string &to) const;
};

#endif
