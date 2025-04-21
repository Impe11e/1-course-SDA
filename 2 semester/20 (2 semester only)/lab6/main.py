from graph import * 
from utils import *

print("\nUndirected matrix:\n")
print_matrix(matrix_undir)

W = get_weights(matrix_undir)

print("\nW:\n")
for row in W:
    print(" ".join(f"{num:4}" for num in row))
print()

def get_edges(matrix, weights):
    edges = []
    size = len(matrix)
    for i in range(size):
        for j in range(i + 1, size):
            if matrix[i][j] == 1:
                edges.append((i, j, weights[i][j]))
    return edges

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)
        if root_u != root_v:
            self.parent[root_v] = root_u
            return True
        return False

def kruskal(matrix, weights):
    edges = get_edges(matrix, weights)
    edges.sort(key=lambda x: x[2])

    uf = UnionFind(len(matrix))
    mst_edges = []

    for u, v, weight in edges:
        if uf.union(u, v):
            mst_edges.append((u, v))

    return mst_edges

edges = get_edges(matrix_undir, W)
mst = kruskal(matrix_undir, W)
print_array(edges, "Edges: ", ", ")
print_array(mst, "MST: ", ", ")
draw_graph(matrix_undir, mst, W)