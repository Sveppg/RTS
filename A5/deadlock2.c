#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct {
    int num_threads;
    int num_resources;
    int num_nodes;
    int **adj_matrix;
} RBGraph;

RBGraph *create_graph(int num_threads, int num_resources) {
    RBGraph *graph = (RBGraph *)malloc(sizeof(RBGraph));
    graph->num_threads = num_threads;
    graph->num_resources = num_resources;
    graph->num_nodes = num_threads + num_resources;

    graph->adj_matrix = malloc(graph->num_nodes * sizeof(int *));
    for (int i = 0; i < graph->num_nodes; i++) {
        graph->adj_matrix[i] = (int *)calloc(graph->num_nodes+1, sizeof(int));
    }

    return graph;
}
/* t...r */
void add_edge(RBGraph *graph, char edge_type, int start, int end) {  // takes start + end as t or r 
    int row = 0;
    int column = 0;
    if (edge_type == 'o') {  // occupied
        row = start + graph->num_threads -1;
        column = end -1;
    } else if (edge_type == 'w') { // waiting for resource
        row = start -1;
        column = end + graph->num_threads - 1;  
    }
    graph->adj_matrix[row][column] = 1;

}

bool dfs(RBGraph *graph, int node, bool *visited, bool *stack) {
    if (!visited[node]) {
        visited[node] = true;
        stack[node] = true;

        for (int neighbor = 0; neighbor < graph->num_nodes; neighbor++) {
            if (graph->adj_matrix[node][neighbor]) {
                if (!visited[neighbor] && dfs(graph, neighbor, visited, stack)) {
                    return true;
                } else if (stack[neighbor]) {
                    return true;
                }
            }
        }
    }
    stack[node] = false;
    return false;
}

bool detect_deadlock(RBGraph *graph) {
    bool *visited = (bool *)calloc(graph->num_nodes, sizeof(bool));
    bool *stack = (bool *)calloc(graph->num_nodes, sizeof(bool));

    for (int node = 0; node < graph->num_nodes; node++) {
        if (dfs(graph, node, visited, stack)) {
            free(visited);
            free(stack);
            return true;
        }
    }

    free(visited);
    free(stack);
    return false;
}


void debug_matrix(RBGraph *graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->num_nodes; i++) {
        for (int j = 0; j < graph->num_nodes; j++) {
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}


RBGraph *load_graph(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    int num_threads, num_resources;
    fscanf(file, "%d", &num_threads);
    fscanf(file, "%d", &num_resources);

    printf("num_threads %d\n", num_threads); // Debugging
    printf("num_resources %d\n", num_resources); // Debugging
    
    RBGraph *graph = create_graph(num_threads, num_resources);

    char edge_type;
    int start, end;
    while (fscanf(file, " %c %d %d", &edge_type, &start, &end) == 3) {
        add_edge(graph, edge_type, start, end);
    }

    fclose(file);
    return graph;
}


void free_graph(RBGraph *graph) {
    for (int i = 0; i < graph->num_nodes; i++) {
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);
}


void save_as_dot(RBGraph *graph, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open dot file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "digraph {\n");

    // Knoten hinzufügen
    for (int i = 0; i < graph->num_threads; i++) {
        fprintf(file, "t%d [style=filled, fillcolor=green];\n", i + 1);
    }
    for (int i = 0; i < graph->num_resources; i++) {
        fprintf(file, "r%d [shape=box, style=filled, fillcolor=orange];\n", i + 1);
    }

    // Kanten hinzufügen
    for (int i = 0; i < graph->num_nodes; i++) {
        for (int j = 0; j < graph->num_nodes; j++) {
            if (graph->adj_matrix[i][j]) {
                if (i >= graph->num_threads) {
                     // Ressource belegt Thread
                    printf("Ressource r%d -> Thread t%d\n", i - graph->num_threads + 1, j + 1);
                    fprintf(file, "r%d -> t%d;\n", i - graph->num_threads + 1, j + 1);
                } else {
                    // Thread wartet auf Ressource
                    printf("Thread t%d -> Ressource r%d\n", i + 1, j - graph->num_threads + 1);
                    fprintf(file, "t%d -> r%d;\n", i + 1, j - graph->num_threads + 1);
                }
            }
        }
    }

    fprintf(file, "}\n");
    fclose(file);
}


int main(int argc, char **argv) {
    if(argc < 3) return 1;
    RBGraph *graph = load_graph(argv[1]);
    debug_matrix(graph);

    if (detect_deadlock(graph)) {
        printf("Deadlock detected!\n");
    } else {
        printf("No deadlock detected.\n");
    }

    save_as_dot(graph, argv[2]);
    printf("Graph saved as dot file: %s\n", argv[2]);

    free_graph(graph);
    return 0;
}

