#ifndef PLACEMENT_ENGINE_H
#define PLACEMENT_ENGINE_H

#include <map>
#include <string>
#include <vector>

#include "models/Graph.h"
#include "models/Position.h"

class PlacementEngine
{
public:
    std::map<std::string, Position> locations;

    explicit PlacementEngine(Graph &graph);

    void placeComponents();

private:
    Graph &graph;

    std::vector<std::string> collectNodes() const;
    void forceDirectedPlacement(const std::vector<std::string> &nodes);
    void resolveOverlaps(const std::vector<std::string> &nodes, int gridUnit);
};

#endif
