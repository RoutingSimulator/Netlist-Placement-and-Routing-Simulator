#include "Netlist.h"
#include <fstream>

using namespace std;

void readNetlist(string filename, Graph &graph)
{
    ifstream file(filename);

    string source, destination;

    while(file >> source >> destination)
    {
        graph.addEdge(source, destination);
    }

    file.close();
}
