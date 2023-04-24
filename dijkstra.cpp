#include <iostream>
#include <vector>

const int INF = 9999999;

class Edge {
public:
    int dest;
    int weight;
};

class Node {
public:
    int accum = INF;
    bool visited = false;
    std::vector<Edge> edges;

    void addEdge(const int dest, const int weight) {
        Edge edge = Edge();
        edge.dest = dest;
        edge.weight = weight;
        this->edges.push_back(edge);
    }
};

int dijkstra(std::vector<Node>& nodes, int start, int end) {
    nodes[start].accum = 0;
    int minPath = -1;
    for (int i = start; i < nodes.size(); i++) {
        if (!nodes[i].visited){
        for (auto& edge:nodes[i].edges) {
            if (nodes[i].accum + edge.weight < nodes[edge.dest].accum) {
                nodes[edge.dest].accum = nodes[i].accum + edge.weight;
            }
        }
        nodes[i].visited = true;
        if (i == end) {
            minPath = nodes[end].accum;
            return minPath;
        }
        }
    }
    return minPath;
}


int main() {
    std::vector<Node> nodes(8);
    nodes[0].addEdge(1, 250);
    nodes[0].addEdge(2, 170);
    nodes[1].addEdge(3, 140);
    nodes[2].addEdge(3, 150);
    nodes[2].addEdge(5, 210);
    nodes[3].addEdge(4, 40);
    nodes[4].addEdge(7, 140);
    nodes[5].addEdge(6, 240);
    nodes[6].addEdge(7, 85);

    int start = 0;
    int end = 7;
    int shortest_path = dijkstra(nodes, start, end);

    if (shortest_path >= 0) {
        std::cout << "The shortest path from " << start << " to " << end << " is " << shortest_path << std::endl;
    }
    return 0;
}
