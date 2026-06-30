#ifndef GRAPH_ANALYZER_H
#define GRAPH_ANALYZER_H

#include <string>

#include "models/Analysis.h"
#include "models/Graph.h"

class GraphAnalyzer
{
public:
    explicit GraphAnalyzer(Graph &graph);

    Analysis analyze(const std::string &startNode);
    Analysis analyzeFromFirstNode();
    void printAnalysis(const Analysis &analysis) const;

private:
    Graph &graph;

    std::vector<std::string> bfs(const std::string &start);
    std::vector<std::string> dfs(const std::string &start);
};

#endif
