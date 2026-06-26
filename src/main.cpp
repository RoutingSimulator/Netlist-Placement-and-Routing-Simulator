#include "Netlist.h"
#include "Graph.h"
#include "Placement.h"
#include "Routing.h"
#include "Visualization.h"

int main() {

    Graph graph;

    readNetlist("netlist.txt", graph);

    graph.print();

    Placement placement(graph);
    placement.placeComponents();

    Routing routing(graph, placement);
    routing.routeConnections();

    Visualization visual(graph, placement);
    visual.display();

    return 0;
}
