#include "visualization/SvgExporter.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace
{
constexpr int kScale = 20;
constexpr int kPadding = 40;
constexpr int kNodeRadius = 12;
}

SvgExporter::SvgExporter(Graph &graph, PlacementEngine &placement, RoutingEngine &routing)
    : graph(graph), placement(placement), routing(routing)
{
}

void SvgExporter::display() const
{
    std::cout << "Placement:" << std::endl;
    for (const auto &entry : placement.locations)
        std::cout << "  " << entry.first << " -> (" << entry.second.x << ", " << entry.second.y << ")" << std::endl;

    routing.printRoutes();
}

bool SvgExporter::exportToFile(const std::string &filename) const
{
    int maxX = 0;
    int maxY = 0;

    for (const auto &entry : placement.locations)
    {
        maxX = std::max(maxX, entry.second.x);
        maxY = std::max(maxY, entry.second.y);
    }

    const int width = maxX * kScale + kPadding * 2 + kNodeRadius * 2;
    const int height = maxY * kScale + kPadding * 2 + kNodeRadius * 2;

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to write SVG file: " << filename << std::endl;
        return false;
    }

    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width
         << "\" height=\"" << height << "\">\n";
    file << "  <rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";

    for (const auto &route : routing.routes)
    {
        for (size_t i = 1; i < route.waypoints.size(); ++i)
        {
            const Position &a = route.waypoints[i - 1];
            const Position &b = route.waypoints[i];
            const int x1 = kPadding + a.x * kScale;
            const int y1 = kPadding + a.y * kScale;
            const int x2 = kPadding + b.x * kScale;
            const int y2 = kPadding + b.y * kScale;

            file << "  <line x1=\"" << x1 << "\" y1=\"" << y1
                 << "\" x2=\"" << x2 << "\" y2=\"" << y2
                 << "\" stroke=\"gray\" stroke-width=\"2\"/>\n";
        }
    }

    for (const auto &entry : placement.locations)
    {
        const int cx = kPadding + entry.second.x * kScale;
        const int cy = kPadding + entry.second.y * kScale;

        file << "  <circle cx=\"" << cx << "\" cy=\"" << cy
             << "\" r=\"" << kNodeRadius << "\" fill=\"lightblue\" stroke=\"black\"/>\n";
        file << "  <text x=\"" << cx << "\" y=\"" << cy + 4
             << "\" text-anchor=\"middle\" font-size=\"12\">" << entry.first << "</text>\n";
    }

    file << "</svg>\n";
    file.close();

    std::cout << "SVG exported to " << filename << std::endl;
    return true;
}
