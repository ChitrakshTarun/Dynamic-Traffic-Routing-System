#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "utils.h"

void initialize_graph(Graph *graph) {
    graph->num_nodes = 0;
    
    // Initialize all road segments as non-existent
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            graph->adjacency_matrix[i][j].destination = -1;
            graph->adjacency_matrix[i][j].is_closed = 0;
        }
    }
}

int find_node_index(Graph *graph, const char *node_name) {
    for (int i = 0; i < graph->num_nodes; i++) {
        if (strcmp(graph->node_names[i], node_name) == 0) {
            return i;
        }
    }
    
    // If node doesn't exist, add it
    if (graph->num_nodes < MAX_NODES) {
        strcpy(graph->node_names[graph->num_nodes], node_name);
        return graph->num_nodes++;
    }
    
    return -1;
}

void add_road_segment(Graph *graph, const char *start, const char *end, 
                      int distance, int traffic_density) {
    int start_index = find_node_index(graph, start);
    int end_index = find_node_index(graph, end);
    
    if (start_index == -1 || end_index == -1) {
        printf("Error: Invalid nodes for road segment\n");
        return;
    }
    
    // Add road segment to adjacency matrix
    strcpy(graph->adjacency_matrix[start_index][end_index].name, end);
    graph->adjacency_matrix[start_index][end_index].destination = end_index;
    graph->adjacency_matrix[start_index][end_index].distance = distance;
    graph->adjacency_matrix[start_index][end_index].traffic_density = traffic_density;
    graph->adjacency_matrix[start_index][end_index].is_closed = 0;
}

void dijkstra_shortest_path(Graph *graph, const char *start, const char *end) {
    int start_index = find_node_index(graph, start);
    int end_index = find_node_index(graph, end);
    
    if (start_index == -1 || end_index == -1) {
        printf("Error: Invalid start or end node\n");
        return;
    }
    
    int distances[MAX_NODES];
    int visited[MAX_NODES];
    int previous[MAX_NODES];
    
    // Initialize
    for (int i = 0; i < graph->num_nodes; i++) {
        distances[i] = INFINITY;
        visited[i] = 0;
        previous[i] = -1;
    }
    
    distances[start_index] = 0;
    
    // Dijkstra's algorithm
    for (int count = 0; count < graph->num_nodes - 1; count++) {
        int min_distance = INFINITY;
        int current_node = -1;
        
        // Find unvisited node with minimum distance
        for (int v = 0; v < graph->num_nodes; v++) {
            if (!visited[v] && distances[v] < min_distance) {
                min_distance = distances[v];
                current_node = v;
            }
        }
        
        if (current_node == -1) break;
        
        visited[current_node] = 1;
        
        // Update distances
        for (int v = 0; v < graph->num_nodes; v++) {
            RoadSegment *road = &graph->adjacency_matrix[current_node][v];
            
            if (road->destination != -1 && !road->is_closed) {
                int route_distance = distances[current_node] + 
                    road->distance * (1 + road->traffic_density / 10.0);
                
                if (route_distance < distances[v]) {
                    distances[v] = route_distance;
                    previous[v] = current_node;
                }
            }
        }
    }
    
    // Print path
    printf("Shortest Path from %s to %s:\n", start, end);
    if (distances[end_index] == INFINITY) {
        printf("No path exists!\n");
        return;
    }
    
    int path[MAX_NODES];
    int path_length = 0;
    int current = end_index;
    
    while (current != -1) {
        path[path_length++] = current;
        current = previous[current];
    }
    
    printf("Total Distance: %d\n", distances[end_index]);
    printf("Route: ");
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%s ", graph->node_names[path[i]]);
    }
    printf("\n");
}

void print_graph(Graph *graph) {
    printf("Graph Nodes:\n");
    for (int i = 0; i < graph->num_nodes; i++) {
        printf("%s:\n", graph->node_names[i]);
        for (int j = 0; j < graph->num_nodes; j++) {
            RoadSegment *road = &graph->adjacency_matrix[i][j];
            if (road->destination != -1) {
                printf("  -> %s (Distance: %d, Traffic: %d, Closed: %s)\n", 
                       road->name, road->distance, road->traffic_density, 
                       road->is_closed ? "Yes" : "No");
            }
        }
    }
}