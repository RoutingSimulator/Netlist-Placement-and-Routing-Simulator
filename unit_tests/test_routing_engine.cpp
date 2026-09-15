#include <gtest/gtest.h>

#include "models/Graph.h"
#include "placement/PlacementEngine.h"
#include "routing/RoutingEngine.h"

TEST(RoutingEngineTest, ProducesRouteForEachEdgeWithEndpoints) {
    Graph graph;
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");

    PlacementEngine placement(graph);
    placement.placeComponents();

    RoutingEngine routing(graph, placement);
    routing.routeConnections();

    const auto &routes = routing.getRoutes();
    ASSERT_EQ(routes.size(), 2u);

    for (const auto &route : routes) {
        ASSERT_GE(route.waypoints.size(), 2u);
        const auto &start = route.waypoints.front();
        const auto &end = route.waypoints.back();
        const auto &fromPos = placement.getLocations().at(route.from);
        const auto &toPos = placement.getLocations().at(route.to);
        EXPECT_EQ(start.x, fromPos.x);
        EXPECT_EQ(start.y, fromPos.y);
        EXPECT_EQ(end.x, toPos.x);
        EXPECT_EQ(end.y, toPos.y);
    }
}
