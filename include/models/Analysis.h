#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <map>
#include <string>
#include <vector>

struct Analysis
{
    std::string startNode;
    std::vector<std::string> bfsOrder;
    std::vector<std::string> dfsOrder;
    std::map<std::string, int> bfsLevels;
};

#endif
