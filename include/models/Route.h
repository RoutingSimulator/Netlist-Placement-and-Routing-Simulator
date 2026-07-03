#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>

#include "models/Position.h"

struct Route
{
    std::string from;
    std::string to;
    std::vector<Position> waypoints;
};

#endif
