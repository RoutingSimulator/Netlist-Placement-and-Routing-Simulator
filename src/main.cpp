#include "parser/NetlistParser.h"
#include "models/Graph.h"
#include "analyzer/GraphAnalyzer.h"
#include "placement/PlacementEngine.h"
#include "routing/RoutingEngine.h"
#include "visualization/SvgExporter.h"

int main()
{
    Graph graph;

    NetlistParser parser;
    if (!parser.parse("netlist.txt", graph))
        return 1;

    graph.print();

    GraphAnalyzer analyzer(graph);
    const Analysis analysis = analyzer.analyzeFromFirstNode();
    analyzer.printAnalysis(analysis);

    PlacementEngine placement(graph);
    placement.placeComponents();

    RoutingEngine routing(graph, placement);
    routing.routeConnections();

    SvgExporter exporter(graph, placement, routing);
    exporter.display();
    exporter.exportToFile("output.svg");

    return 0;
}
