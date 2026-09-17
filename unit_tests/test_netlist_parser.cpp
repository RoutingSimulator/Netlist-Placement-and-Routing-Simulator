#include <fstream>
#include <gtest/gtest.h>

#include "parser/NetlistParser.h"

namespace {

void writeNetlist(const std::string &path, const std::string &content) {
    std::ofstream out(path);
    ASSERT_TRUE(out.is_open());
    out << content;
}

}  // namespace

TEST(NetlistParserTest, ReturnsFalseWhenFileMissing) {
    Graph graph;
    NetlistParser parser;
    EXPECT_FALSE(parser.parse("/nonexistent/netlist_missing.txt", graph));
    EXPECT_TRUE(graph.getNodes().empty());
}

TEST(NetlistParserTest, ParsesValidEdgesAndIgnoresCommentsAndBlankLines) {
    const std::string path = "test_netlist_valid.tmp";
    writeNetlist(path,
                 "# comment\n"
                 "\n"
                 "// line comment\n"
                 "A B\n"
                 "B C\n");

    Graph graph;
    NetlistParser parser;
    ASSERT_TRUE(parser.parse(path, graph));

    const auto edges = graph.getEdges();
    ASSERT_EQ(edges.size(), 2u);
    EXPECT_EQ(edges[0].from, "A");
    EXPECT_EQ(edges[0].to, "B");
    EXPECT_EQ(edges[1].from, "B");
    EXPECT_EQ(edges[1].to, "C");
}

TEST(NetlistParserTest, SkipsSelfLoopsAndInvalidNodeNames) {
    const std::string path = "test_netlist_invalid.tmp";
    writeNetlist(path,
                 "A A\n"
                 "AB C\n"
                 "D\n"
                 "E F\n");

    Graph graph;
    NetlistParser parser;
    ASSERT_TRUE(parser.parse(path, graph));

    const auto edges = graph.getEdges();
    ASSERT_EQ(edges.size(), 1u);
    EXPECT_EQ(edges[0].from, "E");
    EXPECT_EQ(edges[0].to, "F");
}
