/*#include "routing/RoutingEngine.h"

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
*/

#include "routing/RoutingEngine.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

namespace
{
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

bool isEqual(const Position &a, const Position &b)
{
    return a.x == b.x && a.y == b.y;
}

struct PositionCompare
{
    bool operator()(const Position &a, const Position &b) const
    {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    }
};

struct GridNode
{
    Position pos;
    int gCost;
    int hCost;
    int fCost() const { return gCost + hCost; }

    bool operator>(const GridNode &other) const
    {
        return fCost() > other.fCost();
    }
};

int manhattanDistance(const Position &a, const Position &b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Position> findAStarRoute(
    const Position &start,
    const Position &end,
    const std::map<std::string, Position> &locations,
    const std::string &from,
    const std::string &to,
    const std::set<Position, PositionCompare> &usedEdgePoints)
{
    std::set<Position, PositionCompare> obstacles = usedEdgePoints;

    int minX = std::min(start.x, end.x);
    int maxX = std::max(start.x, end.x);
    int minY = std::min(start.y, end.y);
    int maxY = std::max(start.y, end.y);

    for (const auto &entry : locations)
    {
        minX = std::min(minX, entry.second.x);
        maxX = std::max(maxX, entry.second.x);
        minY = std::min(minY, entry.second.y);
        maxY = std::max(maxY, entry.second.y);

        // All nodes other than 'from' and 'to' are strict obstacles
        if (entry.first != from && entry.first != to)
        {
            obstacles.insert(entry.second);
        }
    }

    const int padding = 4;
    minX -= padding;
    maxX += padding;
    minY -= padding;
    maxY += padding;

    std::priority_queue<GridNode, std::vector<GridNode>, std::greater<GridNode>> openSet;
    std::map<Position, Position, PositionCompare> cameFrom;
    std::map<Position, int, PositionCompare> gScore;

    openSet.push({start, 0, manhattanDistance(start, end)});
    gScore[start] = 0;

    bool pathFound = false;

    while (!openSet.empty())
    {
        Position current = openSet.top().pos;
        openSet.pop();

        if (isEqual(current, end))
        {
            pathFound = true;
            break;
        }

        for (int i = 0; i < 4; ++i)
        {
            Position neighbor = {current.x + dx[i], current.y + dy[i]};

            if (neighbor.x < minX || neighbor.x > maxX || neighbor.y < minY || neighbor.y > maxY)
                continue;

            // Block obstacles, but allow start and end positions
            if (obstacles.count(neighbor) && !isEqual(neighbor, end) && !isEqual(neighbor, start))
                continue;

            int newGCost = gScore[current] + 1;

            if (!gScore.count(neighbor) || newGCost < gScore[neighbor])
            {
                gScore[neighbor] = newGCost;
                cameFrom[neighbor] = current;
                openSet.push({neighbor, newGCost, manhattanDistance(neighbor, end)});
            }
        }
    }

    if (!pathFound)
        return {start, end};

    // Reconstruct path
    std::vector<Position> fullPath;
    Position curr = end;
    while (!isEqual(curr, start))
    {
        fullPath.push_back(curr);
        curr = cameFrom[curr];
    }
    fullPath.push_back(start);
    std::reverse(fullPath.begin(), fullPath.end());

    if (fullPath.size() <= 2)
        return fullPath;

    // Simplify waypoints
    std::vector<Position> waypoints;
    waypoints.push_back(fullPath[0]);

    for (size_t i = 1; i < fullPath.size() - 1; ++i)
    {
        int dirX1 = fullPath[i].x - fullPath[i - 1].x;
        int dirY1 = fullPath[i].y - fullPath[i - 1].y;
        int dirX2 = fullPath[i + 1].x - fullPath[i].x;
        int dirY2 = fullPath[i + 1].y - fullPath[i].y;

        if (dirX1 != dirX2 || dirY1 != dirY2)
        {
            waypoints.push_back(fullPath[i]);
        }
    }
    waypoints.push_back(fullPath.back());

    return waypoints;
}
} // namespace

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
    const auto &locations = placement.getLocations();
    std::set<Position, PositionCompare> usedEdgePoints;

    for (const auto &edge : graph.getEdges())
    {
        Route route;
        route.from = edge.from;
        route.to = edge.to;

        const Position start = locations.at(edge.from);
        const Position end = locations.at(edge.to);

        route.waypoints = findAStarRoute(start, end, locations, edge.from, edge.to, usedEdgePoints);
        routes.push_back(route);

        // Mark points between start and end as used (avoiding exact endpoints to allow node connections)
        for (const auto &pt : route.waypoints)
        {
            if (!isEqual(pt, start) && !isEqual(pt, end))
            {
                usedEdgePoints.insert(pt);
            }
        }
    }
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
    const auto &locations = placement.getLocations();
    std::set<Position, PositionCompare> emptyUsed;
    Route route;
    route.from = from;
    route.to = to;
    route.waypoints = findAStarRoute(locations.at(from), locations.at(to), locations, from, to, emptyUsed);
    return route;
}