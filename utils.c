#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "utils.h"

// Seed random number generator
static int is_seeded = 0;

int generate_random(int min, int max) {
    if (!is_seeded) {
        srand(time(NULL));
        is_seeded = 1;
    }
    return min + rand() % (max - min + 1);
}

void simulate_traffic_conditions(Graph *graph) {
    for (int i = 0; i < graph->num_nodes; i++) {
        for (int j = 0; j < graph->num_nodes; j++) {
            RoadSegment *road = &graph->adjacency_matrix[i][j];
            if (road->destination != -1) {
                // Randomly adjust traffic density
                road->traffic_density = generate_random(1, 10);
            }
        }
    }
    printf("Traffic conditions simulated.\n");
}

void simulate_road_closure(Graph *graph) {
    int node1 = generate_random(0, graph->num_nodes - 1);
    int node2 = generate_random(0, graph->num_nodes - 1);
    
    if (node1 != node2) {
        graph->adjacency_matrix[node1][node2].is_closed = 1;
        printf("Road %s -> %s is now closed.\n", 
               graph->node_names[node1], 
               graph->adjacency_matrix[node1][node2].name);
    }
}