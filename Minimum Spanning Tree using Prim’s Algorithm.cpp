#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_SIZE 100
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};
struct Graph {
    int numVertices;
    struct Node** adjLists;
};
struct Node* createNode(int v, int w) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct Node*));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
int minDistance(int distance[], int visitedSet[], int numVertices) {
    int min = INT_MAX, min_index;

    int i;
    for (i = 0; i < numVertices; i++) {
        if (visitedSet[i] == 0 && distance[i] <= min) {
            min = distance[i];
            min_index = i;
        }
    }

    return min_index;
}
void prim(struct Graph* graph, int src) {
    int numVertices = graph->numVertices;
    int parent[numVertices];
    int distance[numVertices];
    int visitedSet[numVertices];

    int i;
    for (i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
        visitedSet[i] = 0;
    }

    distance[src] = 0;
    parent[src] = -1;

    int count;
    for (count = 0; count < numVertices - 1; count++) {
        int u = minDistance(distance, visitedSet, numVertices);
        visitedSet[u] = 1;

        struct Node* temp = graph->adjLists[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (!visitedSet[v] && weight < distance[v]) {
                parent[v] = u;
                distance[v] = weight;
            }

            temp = temp->next;
        }
    }

    printf("Edge \tWeight\n");
    for (i = 1; i < numVertices; i++) {
        printf("%d - %d \t%d \n", parent[i], i, distance[i]);
    }
}
int main() {
    int vertices, edges, i, src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (i = 0; i < edges; i++) {
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    int startVertex;
    printf("Enter the starting vertex for Prim's algorithm: ");
    scanf("%d", &startVertex);

    prim(graph, startVertex);

    return 0;
}
