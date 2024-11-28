#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph.h"
#include "utils.h"

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void print_menu() {
    printf("\n--- Dynamic Traffic Routing System ---\n");
    printf("1. Find Shortest Path\n");
    printf("2. Simulate Traffic Conditions\n");
    printf("3. Close a Road\n");
    printf("4. View Network\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Graph city_network;
    initialize_graph(&city_network);
    
    // Predefined road segments
    add_road_segment(&city_network, "Downtown", "Suburb1", 10, 5);
    add_road_segment(&city_network, "Suburb1", "Industrial", 15, 3);
    add_road_segment(&city_network, "Downtown", "Industrial", 25, 7);
    add_road_segment(&city_network, "Suburb1", "Suburb2", 12, 2);
    add_road_segment(&city_network, "Suburb2", "Airport", 18, 4);
    add_road_segment(&city_network, "Industrial", "Airport", 20, 6);
    
    char start[50], end[50];
    int choice;
    
    while (1) {
        clear_screen();
        print_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter start location: ");
                scanf("%49s", start);
                printf("Enter end location: ");
                scanf("%49s", end);
                dijkstra_shortest_path(&city_network, start, end);
                break;
            
            case 2:
                simulate_traffic_conditions(&city_network);
                printf("Traffic conditions updated.\n");
                break;
            
            case 3:
                simulate_road_closure(&city_network);
                break;
            
            case 4:
                print_graph(&city_network);
                break;
            
            case 5:
                printf("Exiting program.\n");
                return 0;
            
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        while (getchar() != '\n');  // Clear any previous input
        getchar();  // Wait for Enter key
    }
    
    return 0;
}