#include <gtest/gtest.h>

#include "models/Graph.h"

TEST(GraphTest, EmptyGraphHasNoNodesOrEdges) {
    Graph graph;
    EXPECT_TRUE(graph.getNodes().empty());
    EXPECT_TRUE(graph.getEdges().empty());
}

TEST(GraphTest, AddNodeCreatesEntryInAdjacencyList) {
    Graph graph;
    graph.addNode("X");
    ASSERT_EQ(graph.getNodes().size(), 1u);
    EXPECT_EQ(graph.getNodes().front(), "X");
    EXPECT_TRUE(graph.getAdjacencyList().at("X").empty());
}

TEST(GraphTest, AddEdgeCreatesBothNodesAndDirectedEdge) {
    Graph graph;
    graph.addEdge("A", "B");

    const auto edges = graph.getEdges();
    ASSERT_EQ(edges.size(), 1u);
    EXPECT_EQ(edges[0].from, "A");
    EXPECT_EQ(edges[0].to, "B");

    const auto &adj = graph.getAdjacencyList();
    ASSERT_EQ(adj.at("A").size(), 1u);
    EXPECT_EQ(adj.at("A")[0], "B");
}

TEST(GraphTest, ParallelEdgesArePreserved) {
    Graph graph;
    graph.addEdge("A", "B");
    graph.addEdge("A", "B");

    EXPECT_EQ(graph.getEdges().size(), 2u);
    EXPECT_EQ(graph.getAdjacencyList().at("A").size(), 2u);
}
