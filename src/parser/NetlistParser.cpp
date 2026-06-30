#include "parser/NetlistParser.h"

#include <fstream>
#include <iostream>

bool NetlistParser::parse(const std::string &filename, Graph &graph)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open netlist file: " << filename << std::endl;
        return false;
    }

    std::string source;
    std::string destination;

    while (file >> source >> destination)
        graph.addEdge(source, destination);

    file.close();
    return true;
}
