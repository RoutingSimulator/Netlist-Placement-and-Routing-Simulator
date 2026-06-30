#ifndef NETLIST_PARSER_H
#define NETLIST_PARSER_H

#include <string>

#include "models/Graph.h"

class NetlistParser
{
public:
    bool parse(const std::string &filename, Graph &graph);
};

#endif
