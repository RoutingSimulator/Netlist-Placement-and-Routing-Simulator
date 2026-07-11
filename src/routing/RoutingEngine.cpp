#include "routing/RoutingEngine.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

namespace
{
constexpr int kDetourMargin = 2;

bool pointOnSegment(const Position &point, const Position &a, const Position &b)
{
    if (a.x == b.x && a.y == b.y)
        return point.x == a.x && point.y == a.y;

    if (a.y == b.y)
    {
        const int minX = std::min(a.x, b.x);
        const int maxX = std::max(a.x, b.x);
        return point.y == a.y && point.x >= minX && point.x <= maxX;
    }

    if (a.x == b.x)
    {
        const int minY = std::min(a.y, b.y);
        const int maxY = std::max(a.y, b.y);
        return point.x == a.x && point.y >= minY && point.y <= maxY;
    }

    return false;
}

bool segmentBlocked(
    const Position &a,
    const Position &b,
    const std::map<std::string, Position> &locations,
    const std::string &from,
    const std::string &to)
{
    for (const auto &entry : locations)
    {
        if (entry.first == from || entry.first == to)
            continue;

        if (pointOnSegment(entry.second, a, b))
            return true;
    }

    return false;
}

bool routeBlocked(
    const std::vector<Position> &waypoints,
    const std::map<std::string, Position> &locations,
    const std::string &from,
    const std::string &to)
{
    if (waypoints.size() < 2)
        return false;

    for (size_t i = 1; i < waypoints.size(); ++i)
    {
        if (segmentBlocked(waypoints[i - 1], waypoints[i], locations, from, to))
            return true;
    }

    return false;
}

std::vector<Position> buildHorizontalFirstRoute(const Position &start, const Position &end)
{
    if (start.x == end.x || start.y == end.y)
        return {start, end};

    return {start, {end.x, start.y}, end};
}

std::vector<Position> buildVerticalFirstRoute(const Position &start, const Position &end)
{
    if (start.x == end.x || start.y == end.y)
        return {start, end};

    return {start, {start.x, end.y}, end};
}

std::vector<Position> buildChannelRoute(
    const Position &start,
    const Position &end,
    int channelX,
    bool useVerticalChannel)
{
    if (useVerticalChannel)
        return {start, {channelX, start.y}, {channelX, end.y}, end};

    return {start, {start.x, channelX}, {end.x, channelX}, end};
}

int minCoordinate(const std::map<std::string, Position> &locations, bool useX)
{
    int value = 0;
    bool initialized = false;

    for (const auto &entry : locations)
    {
        const int coordinate = useX ? entry.second.x : entry.second.y;
        if (!initialized || coordinate < value)
        {
            value = coordinate;
            initialized = true;
        }
    }

    return initialized ? value : 0;
}

int maxCoordinate(const std::map<std::string, Position> &locations, bool useX)
{
    int value = 0;
    bool initialized = false;

    for (const auto &entry : locations)
    {
        const int coordinate = useX ? entry.second.x : entry.second.y;
        if (!initialized || coordinate > value)
        {
            value = coordinate;
            initialized = true;
        }
    }

    return initialized ? value : 0;
}

std::vector<Position> buildDetourRoute(
    const Position &start,
    const Position &end,
    const std::map<std::string, Position> &locations,
    const std::string &from,
    const std::string &to)
{
    const int minX = minCoordinate(locations, true);
    const int maxX = maxCoordinate(locations, true);
    const int minY = minCoordinate(locations, false);
    const int maxY = maxCoordinate(locations, false);

    const std::vector<int> horizontalChannels = {
        minY - kDetourMargin,
        maxY + kDetourMargin,
        start.y - kDetourMargin,
        start.y + kDetourMargin,
        end.y - kDetourMargin,
        end.y + kDetourMargin,
    };

    for (const int channelY : horizontalChannels)
    {
        const std::vector<Position> candidate = {
            start,
            {start.x, channelY},
            {end.x, channelY},
            end,
        };

        if (!routeBlocked(candidate, locations, from, to))
            return candidate;
    }

    const std::vector<int> verticalChannels = {
        minX - kDetourMargin,
        maxX + kDetourMargin,
        start.x - kDetourMargin,
        start.x + kDetourMargin,
        end.x - kDetourMargin,
        end.x + kDetourMargin,
    };

    for (const int channelX : verticalChannels)
    {
        const std::vector<Position> candidate = buildChannelRoute(start, end, channelX, true);
        if (!routeBlocked(candidate, locations, from, to))
            return candidate;
    }

    return buildHorizontalFirstRoute(start, end);
}
}

RoutingEngine::RoutingEngine(const Graph &graph, const PlacementEngine &placement)
    : graph(graph), placement(placement)
{
}

const std::vector<Route> &RoutingEngine::getRoutes() const
{
    return routes;
}

void RoutingEngine::routeConnections()
{
    routes.clear();

    for (const auto &edge : graph.getEdges())
        routes.push_back(routeEdge(edge.from, edge.to));
}

void RoutingEngine::printRoutes() const
{
    std::cout << "Routes:" << std::endl;

    for (const auto &route : routes)
    {
        std::cout << route.from << " -> " << route.to << ": ";

        for (size_t i = 0; i < route.waypoints.size(); ++i)
        {
            const Position &point = route.waypoints[i];
            std::cout << "(" << point.x << ", " << point.y << ")";

            if (i + 1 < route.waypoints.size())
                std::cout << " -> ";
        }

        std::cout << std::endl;
    }
}

Route RoutingEngine::routeEdge(const std::string &from, const std::string &to) const
{
    Route route;
    route.from = from;
    route.to = to;

    const auto &locations = placement.getLocations();
    const Position start = locations.at(from);
    const Position end = locations.at(to);

    const std::vector<std::vector<Position>> candidates = {
        buildHorizontalFirstRoute(start, end),
        buildVerticalFirstRoute(start, end),
    };

    for (const auto &candidate : candidates)
    {
        if (!routeBlocked(candidate, locations, from, to))
        {
            route.waypoints = candidate;
            return route;
        }
    }

    route.waypoints = buildDetourRoute(start, end, locations, from, to);
    return route;
}
