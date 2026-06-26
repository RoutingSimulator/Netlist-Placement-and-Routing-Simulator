#ifndef PLACEMENT_H
#define PLACEMENT_H

#include <map>
#include <string>
#include "Graph.h"

struct Position
{
    int x;
    int y;
};

class Placement
{
public:
    std::map<std::string, Position> locations;

    Placement(Graph &graph);

    void placeComponents();
};

#endif
