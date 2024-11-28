#ifndef UTILS_H
#define UTILS_H

#include "graph.h"

// Random number generator functions
int generate_random(int min, int max);
void simulate_traffic_conditions(Graph *graph);
void simulate_road_closure(Graph *graph);

#endif // UTILS_H