from graph import * 
from utils import *
from collections import deque

def bfs_tree(matrix, start):
    print("\nBFS traversal order:")
    n = len(matrix)
    visited = set()
    tree = [[0] * n for _ in range(n)]
    queue = deque([start])
    visited.add(start)
    parent = [-1] * n
    paths = []
    order = 1
    vertex_order = {}

    while queue:
        node = queue.popleft()
        vertex_order[node] = order
        print(f"{node + 1} -> {order}")
        order += 1

        for neighbor in range(n):
            if matrix[node][neighbor] == 1 and neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
                tree[node][neighbor] = 1
                parent[neighbor] = node
                paths.append([node, neighbor])

    return [tree, paths, vertex_order]

def dfs_tree(matrix, start):
    print("\nDFS traversal order:")
    n = len(matrix)
    visited = set()
    tree = [[0] * n for _ in range(n)]
    stack = [(start, -1)]
    paths = []
    order = 1
    vertex_order = {}

    while stack:
        node, parent = stack.pop()
        if node in visited:
            continue
        visited.add(node)

        vertex_order[node] = order
        print(f"{node + 1} -> {order}")
        order += 1

        if parent != -1:
            tree[parent][node] = 1
            paths.append([parent, node])

        for neighbor in range(n - 1, -1, -1):
            if matrix[node][neighbor] == 1 and neighbor not in visited:
                stack.append((neighbor, node))

    return [tree, paths, vertex_order]

print("\nDirected matrix:\n")
print_matrix(matrix_dir)

bfs_tree_result = bfs_tree(matrix_dir, 0)
bfs = bfs_tree_result[0]
bfs_paths = bfs_tree_result[1]
bfs_order = bfs_tree_result[2]

dfs_tree_result = dfs_tree(matrix_dir, 0)
dfs = dfs_tree_result[0]
dfs_paths = dfs_tree_result[1]
dfs_order = dfs_tree_result[2]

print("\nBFS tree:\n")
print_matrix(bfs)

print("\nDFS tree:\n")
print_matrix(dfs)

print("\nBFS vertex order:")
print(bfs_order)

print("\nDFS vertex order:")
print(dfs_order)

draw_graph(matrix_dir, dfs_paths)
