#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 5
#define MAX_EDGES_PER_NODE 10

struct Edge {
    int dest;
    int weight;
};

struct Node {
    int index;
    int visited;
    int accum;
    int current_edges_num;
    struct Edge* edges;
};

struct Node* initNode(struct Node* node, int index) {
    node->index = index-1;
    node->visited = 0;
    node->accum = 9999999;
    node->current_edges_num = 0;
    node->edges = malloc(sizeof(struct Edge)*MAX_EDGES_PER_NODE);
    return node;
}

void addEdge(struct Node* node, int dest, int weight) {
    node->current_edges_num++;
    node->edges = realloc(node->edges, sizeof(struct Edge) * node->current_edges_num);
    node->edges[node->current_edges_num-1].dest = dest - 1;
    node->edges[node->current_edges_num-1].weight = weight;
}

struct Dijkstra {
    struct Node* nodes[MAX_NODES];
    int start;
    int end;
};

void initDijkstra(struct Dijkstra* dijkstra, struct Node* nodes[], int start, int end) {
    dijkstra -> start = start-1;
    dijkstra -> end = end-1;
    for (int i = 0; i < MAX_NODES; i++) {
        dijkstra -> nodes[i] = nodes[i];
    }
};

void shortest_path(struct Dijkstra* dijk){
    int shortestPath = 0;
    dijk->nodes[dijk->start]->accum=0;
    int run = 1;
    while (run==1){
        run = 0;
        for (int i = 0; i < MAX_NODES; i++) 
        {   
            if (dijk->nodes[i]->visited == 0 && dijk->nodes[i]->current_edges_num > 0) {
                for (int j = 0; j < dijk->nodes[i]->current_edges_num; j++) {
                    if (dijk->nodes[i]->edges[j].weight + dijk->nodes[i]->accum < dijk->nodes[dijk->nodes[i]->edges[j].dest]->accum) {
                        dijk->nodes[dijk->nodes[i]->edges[j].dest]->accum = dijk->nodes[i]->edges[j].weight + dijk->nodes[i]->accum;
                    }
                }
                dijk->nodes[i]->visited = 1;
                run = 1;
            }
        }
    }
    shortestPath = dijk->nodes[dijk->end]->accum;
    printf("%d\n", shortestPath);
}

int main() {

    struct Node* nodes[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++) {
        struct Node* node = malloc(sizeof(struct Node));
        nodes[i] = initNode(node, i+1);
    }
    addEdge(nodes[0], 3, 5);
    addEdge(nodes[0], 2, 4);
    addEdge(nodes[1], 5, 10);
    addEdge(nodes[2], 2, 7);
    addEdge(nodes[2], 4, 13);
    addEdge(nodes[2], 5, 2);
    addEdge(nodes[4], 4, 9);

    struct Dijkstra* dijkstra = malloc(sizeof(struct Dijkstra));
    initDijkstra(dijkstra, nodes, 1, 4);
    shortest_path(dijkstra);

    for (int i =  0; i < MAX_NODES; i++){
        free(nodes[i]->edges);  
    }

    // then free nodes
    for (int i = 0; i < MAX_NODES; i++) {
        free(nodes[i]);
    }

    free(dijkstra);
    return 0;
}