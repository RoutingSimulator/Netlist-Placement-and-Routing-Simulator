#ifndef ROUTING_H
#define ROUTING_H

#include "Graph.h"
#include "Placement.h"

class Routing
{
public:

    Routing(Graph &g, Placement &p);

    void routeConnections();
};

#endif
