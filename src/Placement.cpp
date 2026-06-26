#include "Placement.h"

Placement::Placement(Graph &graph)
{
}

void Placement::placeComponents()
{
    locations["A"] = {0,0};
    locations["B"] = {2,0};
    locations["C"] = {0,2};
    locations["D"] = {2,2};
}
