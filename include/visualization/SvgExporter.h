#ifndef SVG_EXPORTER_H
#define SVG_EXPORTER_H

#include <string>

#include "models/Graph.h"
#include "placement/PlacementEngine.h"
#include "routing/RoutingEngine.h"

class SvgExporter
{
public:
    SvgExporter(const Graph &graph, const PlacementEngine &placement, const RoutingEngine &routing);

    void display() const;
    bool exportToFile(const std::string &filename) const;

private:
    const Graph &graph;
    const PlacementEngine &placement;
    const RoutingEngine &routing;
};

#endif
