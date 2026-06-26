#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "Graph.h"
#include "Placement.h"

class Visualization
{
public:

    Visualization(Graph &g, Placement &p);

    void display();
};

#endif
