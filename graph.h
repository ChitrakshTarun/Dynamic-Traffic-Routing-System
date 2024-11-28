#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 100
#define MAX_NAME_LENGTH 50
#define INFINITY 999999

// Road segment structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int destination;
    int distance;
    int traffic_density;
    int is_closed;
} RoadSegment;

// Graph structure
typedef struct {
    int num_nodes;
    char node_names[MAX_NODES][MAX_NAME_LENGTH];
    RoadSegment adjacency_matrix[MAX_NODES][MAX_NODES];
} Graph;

// Function prototypes
void initialize_graph(Graph *graph);
int find_node_index(Graph *graph, const char *node_name);
void add_road_segment(Graph *graph, const char *start, const char *end, 
                      int distance, int traffic_density);
void dijkstra_shortest_path(Graph *graph, const char *start, const char *end);
void a_star_shortest_path(Graph *graph, const char *start, const char *end);
void print_graph(Graph *graph);

#endif // GRAPH_H