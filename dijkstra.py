class Edge:
    def __init__(self, dest, weight):
        self.dest = dest - 1
        self.weight = weight

class Node:
    def __init__(self, edges, index):
        self.edges = edges
        self.index = index-1
        self.visited = False
        self.weight = float('inf')

class Dijkstra:
    def __init__(self, nodes, start, end):
        self.nodes = nodes
        self.start = start - 1
        self.end = end - 1

    def run(self):
        nodes = self.nodes
        nodes[self.start].weight = 0
        shortest_path = float('inf')
        running = True
        while running:
            running = False
            # Iterate over the edges of unvisited nodes
            for node in nodes:
                if not node.visited and node.index >= self.start:
                    for edge in node.edges:
                        if node.weight + edge.weight < nodes[edge.dest].weight:
                            nodes[edge.dest].weight = node.weight + edge.weight
                        if edge.dest == self.end:
                            shortest_path = nodes[edge.dest].weight

                    node.visited = True
                    running = True

        return shortest_path

node1 = [Edge(2, 5),
         Edge(3, 5),
         Edge(4, 5)]

node2 = [Edge(5, 3),
         Edge(3, 2),
         Edge(4, 9)]

node3 = [Edge(4, 8)]

node4 = [Edge(5, 1)]

node5 = []

nodes = [Node(node1, 1),
         Node(node2, 2),
         Node(node3, 3),
         Node(node4, 4),
         Node(node5, 5)]

start = 1
end = 5
shortestPath = Dijkstra(nodes, start, end).run()
print(f"the shortest path from N{start} to N{end} is: {shortestPath}")
