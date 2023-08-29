#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
struct Edge {
    int src, dest, weight;
};
struct Graph {
    int numVertices, numEdges;
    struct Edge* edges;
};
struct Graph* createGraph(int vertices, int edges) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->numEdges = edges;
    graph->edges = malloc(edges * sizeof(struct Edge));
    return graph;
}
int find(int parent[], int i) {
    if (parent[i] == -1) {
        return i;
    }
    return find(parent, parent[i]);
}
void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}
void kruskal(struct Graph* graph) {
    int numVertices = graph->numVertices;
    struct Edge result[numVertices];
    int e = 0;
    int i = 0;

    qsort(graph->edges, graph->numEdges, sizeof(graph->edges[0]), cmp);

    int parent[numVertices];
    memset(parent, -1, sizeof(parent));

    while (e < numVertices - 1 && i < graph->numEdges) {
        struct Edge next_edge = graph->edges[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            unionSet(parent, x, y);
        }
    }

    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d \t%d \n", result[i].src, result[i].dest, result[i].weight);
    }
}
int main() {
    int vertices, edges, i, src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    struct Graph* graph = createGraph(vertices, edges);

    for (i = 0; i < edges; i++) {
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        graph->edges[i].src = src;
        graph->edges[i].dest = dest;
        graph->edges[i].weight = weight;
    }

    kruskal(graph);

    return 0;
}
