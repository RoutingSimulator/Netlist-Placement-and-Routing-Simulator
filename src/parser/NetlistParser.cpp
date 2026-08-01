#include "parser/NetlistParser.h"

#include <fstream>
#include <iostream>
#include <sstream>

bool NetlistParser::parse(const std::string &filename, Graph &graph)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Failed to open netlist file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;

        std::istringstream lineStream(line);
        std::string source;
        std::string destination;
        std::string extraToken;

        // Read source node (skip empty lines)
        if (!(lineStream >> source))
        {
            continue;
        }

        // Ignore comment lines (# or //)
        if (source.rfind("#", 0) == 0 || source.rfind("//", 0) == 0)
        {
            continue;
        }

        // Read destination node (handle missing token)
        if (!(lineStream >> destination))
        {
            std::cerr << "Warning: Syntax error at line " << lineNumber
                      << ": Missing destination node for source '" << source << "'. Skipping line." << std::endl;
            continue;
        }

        // Check node name length (Single character check)
        if (source.length() != 1 || destination.length() != 1)
        {
            std::cerr << "Warning: Syntax error at line " << lineNumber
                      << ": Node names must be a single character ('" << source << "', '" << destination << "'). Skipping line." << std::endl;
            continue;
        }

        // Handle extra tokens on the same line
        if (lineStream >> extraToken)
        {
            std::cerr << "Warning: Syntax error at line " << lineNumber
                      << ": Unexpected extra tokens after '" << destination << "'. Skipping extra tokens." << std::endl;
        }

        // Logical Check: Prevent Self-Loops (A -> A)
        if (source == destination)
        {
            std::cerr << "Warning: Logical error at line " << lineNumber
                      << ": Self-loop detected ('" << source << " -> " << destination
                      << "'). Skipping edge." << std::endl;
            continue;
        }

        graph.addEdge(source, destination);
    }

    file.close();
    return true;
}