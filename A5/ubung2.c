#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000

int adj[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int recStack[MAX_NODES];

int T, R; // number of threads and resources
int totalNodes;

typedef struct {
    char type; // 'o' or 'w'
    int start;
    int end;
} Edge;

Edge edges[MAX_NODES];
int edgeCount = 0;

// DFS-based cycle detection
int dfs(int v) {
    visited[v] = 1;
    recStack[v] = 1;
    for (int w = 0; w < totalNodes; w++) {
        if (adj[v][w] == 1) {
            if (!visited[w]) {
                if (dfs(w))
                    return 1;
            } else if (recStack[w]) {
                // cycle detected
                return 1;
            }
        }
    }
    recStack[v] = 0;
    return 0;
}

int detectCycle() {
    for (int i = 0; i < totalNodes; i++) {
        visited[i] = 0;
        recStack[i] = 0;
    }

    for (int i = 0; i < totalNodes; i++) {
        if (!visited[i]) {
            if (dfs(i)) {
                return 1; // cycle found
            }
        }
    }
    return 0;
}

int main() {
    // Read number of threads and resources
    if (scanf("%d", &T) != 1) {
        fprintf(stderr, "Error reading threads count.\n");
        return 1;
    }
    if (scanf("%d", &R) != 1) {
        fprintf(stderr, "Error reading resources count.\n");
        return 1;
    }

    totalNodes = T + R;

    // Initialize adjacency matrix
    for (int i = 0; i < totalNodes; i++) {
        for (int j = 0; j < totalNodes; j++) {
            adj[i][j] = 0;
        }
    }

    // Read edges until EOF
    char type;
    int start, end;
    edgeCount = 0;
    while (scanf(" %c %d %d", &type, &start, &end) == 3) {
        edges[edgeCount].type = type;
        edges[edgeCount].start = start;
        edges[edgeCount].end = end;
        edgeCount++;

        // Convert to zero-based indices for adjacency
        if (type == 'o') {
            // occupied: resource -> thread
            int resIdx = T + (start - 1); // resource index
            int thrIdx = (end - 1);       // thread index
            adj[resIdx][thrIdx] = 1;
        } else if (type == 'w') {
            // waiting: thread -> resource
            int thrIdx = (start - 1);       
            int resIdx = T + (end - 1);     
            adj[thrIdx][resIdx] = 1;
        } else {
            fprintf(stderr, "Unknown edge type.\n");
            return 1;
        }
    }

    // Detect cycle
    int cycleFound = detectCycle();

    // Print result to stderr (so it doesn't pollute the dot output)
    if (cycleFound) {
        fprintf(stderr, "Deadlock detected.\n");
    } else {
        fprintf(stderr, "No deadlock.\n");
    }

    // Print the DOT output to stdout
    // DOT header
    printf("digraph {\n");

    // Print resources as orange boxes
    for (int i = 1; i <= R; i++) {
        printf("  r%d [shape=box, style=filled, fillcolor=\"orange\"];\n", i);
    }

    // Print threads as green filled nodes
    for (int i = 1; i <= T; i++) {
        printf("  t%d [style=filled, fillcolor=\"green\"];\n", i);
    }

    // Print edges
    for (int i = 0; i < edgeCount; i++) {
        if (edges[i].type == 'o') {
            // resource -> thread
            printf("  r%d -> t%d;\n", edges[i].start, edges[i].end);
        } else if (edges[i].type == 'w') {
            // thread -> resource
            printf("  t%d -> r%d;\n", edges[i].start, edges[i].end);
        }
    }

    // Close DOT
    printf("}\n");

    return 0;
}

