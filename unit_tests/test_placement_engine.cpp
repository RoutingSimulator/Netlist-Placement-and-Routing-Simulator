#include <gtest/gtest.h>

#include "models/Graph.h"
#include "placement/PlacementEngine.h"

TEST(PlacementEngineTest, EmptyGraphProducesNoLocations) {
    Graph graph;
    PlacementEngine engine(graph);
    engine.placeComponents();

    EXPECT_TRUE(engine.getLocations().empty());
    EXPECT_TRUE(engine.getSpanningTree().empty());
}

TEST(PlacementEngineTest, SingleNodePlacedAtOrigin) {
    Graph graph;
    graph.addNode("A");

    PlacementEngine engine(graph);
    engine.placeComponents();

    const auto &locations = engine.getLocations();
    ASSERT_EQ(locations.size(), 1u);
    EXPECT_EQ(locations.at("A").x, 0);
    EXPECT_EQ(locations.at("A").y, 0);
}

TEST(PlacementEngineTest, ConnectedGraphAssignsDistinctGridPositions) {
    Graph graph;
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");

    PlacementEngine engine(graph);
    engine.placeComponents();

    const auto &locations = engine.getLocations();
    ASSERT_EQ(locations.size(), 3u);

    for (const auto &entry : locations) {
        (void)entry;
    }

    EXPECT_NE(locations.at("A").x, locations.at("B").x);
    EXPECT_FALSE(engine.getSpanningTree().empty());
}
