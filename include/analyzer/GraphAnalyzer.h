#ifndef GRAPH_ANALYZER_H
#define GRAPH_ANALYZER_H

#include <string>

#include "models/Analysis.h"
#include "models/Graph.h"

class GraphAnalyzer
{
public:
    explicit GraphAnalyzer(const Graph &graph);

    Analysis analyze(const std::string &startNode) const;
    Analysis analyzeFromFirstNode() const;
    void printAnalysis(const Analysis &analysis) const;

private:
    const Graph &graph;

    std::vector<std::string> bfs(const std::string &start) const;
    std::vector<std::string> dfs(const std::string &start) const;
};

#endif
