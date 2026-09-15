#include <gtest/gtest.h>

#include "analyzer/GraphAnalyzer.h"
#include "models/Graph.h"

namespace {

Graph buildSampleGraph() {
    Graph graph;
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "D");
    graph.addEdge("C", "D");
    graph.addEdge("D", "E");
    graph.addEdge("A", "F");
    graph.addEdge("A", "D");
    return graph;
}

}  // namespace

TEST(GraphAnalyzerTest, BfsFromStartVisitsReachableNodesWithCorrectLevels) {
    const Graph graph = buildSampleGraph();
    GraphAnalyzer analyzer(graph);

    const Analysis analysis = analyzer.analyze("A");

    EXPECT_EQ(analysis.startNode, "A");
    ASSERT_FALSE(analysis.bfsOrder.empty());
    EXPECT_EQ(analysis.bfsOrder.front(), "A");
    EXPECT_EQ(analysis.bfsLevels.at("A"), 0);
    EXPECT_EQ(analysis.bfsLevels.at("B"), 1);
    EXPECT_EQ(analysis.bfsLevels.at("C"), 1);
    EXPECT_EQ(analysis.bfsLevels.at("F"), 1);
    EXPECT_EQ(analysis.bfsLevels.at("D"), 1);
    EXPECT_EQ(analysis.bfsLevels.at("E"), 2);
    EXPECT_EQ(analysis.bfsOrder.size(), 6u);
}

TEST(GraphAnalyzerTest, DfsFromStartIncludesAllReachableNodes) {
    const Graph graph = buildSampleGraph();
    GraphAnalyzer analyzer(graph);

    const Analysis analysis = analyzer.analyze("A");

    ASSERT_EQ(analysis.dfsOrder.size(), 6u);
    EXPECT_EQ(analysis.dfsOrder.front(), "A");
}

TEST(GraphAnalyzerTest, AnalyzeFromFirstNodeUsesFirstGraphNode) {
    Graph graph;
    graph.addEdge("A", "B");

    GraphAnalyzer analyzer(graph);
    const Analysis analysis = analyzer.analyzeFromFirstNode();

    // getNodes() follows std::map key order (alphabetical).
    EXPECT_EQ(analysis.startNode, "A");
    ASSERT_EQ(analysis.bfsOrder.size(), 2u);
}

TEST(GraphAnalyzerTest, EmptyGraphReturnsEmptyAnalysis) {
    Graph graph;
    GraphAnalyzer analyzer(graph);
    const Analysis analysis = analyzer.analyzeFromFirstNode();

    EXPECT_TRUE(analysis.startNode.empty());
    EXPECT_TRUE(analysis.bfsOrder.empty());
    EXPECT_TRUE(analysis.dfsOrder.empty());
}
