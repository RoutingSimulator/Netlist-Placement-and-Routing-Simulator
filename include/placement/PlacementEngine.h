#ifndef PLACEMENT_ENGINE_H
#define PLACEMENT_ENGINE_H

#include <map>
#include <string>
#include <vector>

#include "models/Edge.h"
#include "models/Graph.h"
#include "models/Position.h"

class PlacementEngine
{
public:
    std::map<std::string, Position> locations;
    std::vector<Edge> spanningTree;

    explicit PlacementEngine(Graph &graph);

    void placeComponents();

private:
    Graph &graph;
    static constexpr int gridUnit = 2;

    std::string selectRootNode() const;
    std::map<std::string, std::vector<std::string>> buildUndirectedAdjacency() const;
    std::map<std::string, int> computeLayers(const std::string &root);
    void placeByLayers(const std::map<std::string, int> &layers);
};

#endif
