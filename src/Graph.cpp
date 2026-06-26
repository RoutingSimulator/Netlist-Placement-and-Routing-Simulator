#include "Graph.h"
#include <iostream>

using namespace std;

void Graph::addEdge(string from, string to)
{
    adjacencyList[from].push_back(to);
}

void Graph::print()
{
    for(auto node : adjacencyList)
    {
        cout << node.first << " : ";

        for(string n : node.second)
            cout << n << " ";

        cout << endl;
    }
}
