from graph import * 
from utils import *

def get_graph_info(matrix, isDirected):
    in_degrees = []
    out_degrees = []
    vertex_degrees = []

    print()

    if (isDirected): 
        for i in range(vertexes):
            in_degree = 0
            for j in range(vertexes):
                if(matrix[j][i] == 1):
                    in_degree += 1
            in_degrees.append(in_degree)

        print_array(in_degrees, "Vertex degrees (IN):", " ")

        for i in range(vertexes):
            out_degree = 0
            for j in range(vertexes):
                if(matrix[i][j] == 1):
                    out_degree += 1
            out_degrees.append(out_degree)

        print_array(out_degrees, "Vertex degrees (OUT):", " ")

        for i in range(len(in_degrees)):
            vertex_degrees.append(in_degrees[i] + out_degrees[i])

        print_array(vertex_degrees, "Vertex degrees:", " ")
    else:
        for i in range(vertexes):
            vertex_degree = 0
            for j in range(vertexes):
                if(matrix[i][j] == 1):
                    if(i == j):
                        vertex_degree += 2 
                    else:
                        vertex_degree += 1
            vertex_degrees.append(vertex_degree)
        print_array(vertex_degrees, "Vertex degrees:", " ")

    is_regular = True
    for i in range(len(vertex_degrees)):
        if(vertex_degrees[0] != vertex_degrees[i]): is_regular = False

    if(is_regular):
        print_array([is_regular], "Is regular:", " ")
        print_array([vertex_degrees[0]], "Regularity degree:", " ")
    else: 
        print_array([is_regular], "Is regular:", " ")

    index = 1
    leap_vertexes = []
    isolated_vertexes = []
    for i in vertex_degrees:
        if (i == 0):
            isolated_vertexes.append(index)
        elif (i == 1):
            leap_vertexes.append(index)
        index += 1

    print_array(leap_vertexes, "Leap vertexes:", " ")
    print_array(isolated_vertexes, "Isolated vertexes:", " ")

def log_paths_length_2(matrix):
    vertex_count = len(matrix)
    squared = matrix_multiply(matrix, matrix)
    paths = []
    
    for i in range(vertex_count):
        for j in range(vertex_count):
            if squared[i][j] > 0:
                for k in range(vertex_count):
                    if matrix[i][k] == 1 and matrix[k][j] == 1:
                        paths.append(f"{i+1} -> {k+1} -> {j+1}")
    
    return paths

def log_paths_length_3(matrix):
    vertex_count = len(matrix)
    cubed = matrix_multiply(matrix_multiply(matrix, matrix), matrix)
    paths = []
    
    for i in range(vertex_count):
        for j in range(vertex_count):
            if cubed[i][j] > 0:
                for k in range(vertex_count):
                    for l in range(vertex_count):
                        if matrix[i][k] == 1 and matrix[k][l] == 1 and matrix[l][j] == 1:
                            paths.append(f"{i+1} -> {k+1} -> {l+1} -> {j+1}")
    
    return paths

def reachability_matrix(matrix):
    vertex_count = len(matrix)
    reach = [row[:] for row in matrix]
    matrix_to_power = [row[:] for row in matrix]

    for _ in range(vertex_count - 1):
        matrix_to_power = matrix_multiply(matrix_to_power, matrix)
        reach = matrix_add(reach, matrix_to_power)

    for i in range(vertex_count):
        for j in range(vertex_count):
            if reach[i][j] > 0:
                reach[i][j] = 1
    return reach

def connectivity_matrix(matrix): 
    n = len(matrix)
    connectivity = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if matrix[i][j] == 1 and matrix[j][i] == 1:
                connectivity[i][j] = 1
    return connectivity

def find_strong_components(conn):
    visited = [False] * len(conn)
    components = []

    for v in range(len(conn)):
        if not visited[v]:
            component = []
            for u in range(len(conn)):
                if conn[v][u] == 1:
                    component.append(u + 1)
                    visited[u] = True

            if not component:
                component = [v + 1]
            
            components.append(component)

    return components

def condensed_graph_matrix(graph, sccs):
    n = len(sccs)
    condensed = [[0] * n for _ in range(n)]

    vertex_to_scc = {}
    for scc_index, scc in enumerate(sccs):
        for vertex in scc:
            vertex_to_scc[vertex] = scc_index

    for i in range(len(graph)):
        for j in range(len(graph)):
            if graph[i][j] == 1:
                scc_i = vertex_to_scc[i + 1]
                scc_j = vertex_to_scc[j + 1]
                if scc_i != scc_j:
                    condensed[scc_i][scc_j] = 1

    return condensed

def get_graph_new_info(matrix):
    in_degrees = []
    out_degrees = []

    print()
    for i in range(vertexes):
        in_degree = 0
        for j in range(vertexes):
            if(matrix[j][i] == 1):
                in_degree += 1
        in_degrees.append(in_degree)
    print_array(in_degrees, "Vertex degrees (IN):", " ")
    for i in range(vertexes):
        out_degree = 0
        for j in range(vertexes):
            if(matrix[i][j] == 1):
                out_degree += 1
        out_degrees.append(out_degree)
    print_array(out_degrees, "Vertex degrees (OUT):", " ")

    print_array(log_paths_length_2(matrix), "All paths of 2:", "; ")
    print_array(log_paths_length_3(matrix), "All paths of 3:", "; ")

    print("\nReachability matrix:\n")
    print_matrix(reachability_matrix(matrix))

    print("\nConnectivity matrix:\n")
    print_matrix(connectivity_matrix(reachability_matrix(matrix)))

    scc = find_strong_components(connectivity_matrix(reachability_matrix(matrix)))

    print("\nStrong connectivity components:\n")
    for i in range(len(scc)):
        print(f"{i + 1}) {scc[i]}", end = "\n")

    condensed = condensed_graph_matrix(new_matrix_dir, scc)

    print("\nCondensed graph matrix:\n")
    print_matrix(condensed)

    draw_graph(condensed, len(condensed), 1)
    
print("\nDirected matrix:\n")
print_matrix(matrix_dir)
get_graph_info(matrix_dir, True)

print("\nUndirected matrix:\n")
print_matrix(matrix_undir)
get_graph_info(matrix_undir, False)

new_matrix_dir = [[0 for _ in range(vertexes)] for _ in range(vertexes)]

for i in range(vertexes):
    for j in range(vertexes):
        new_matrix_dir[i][j] = calculate_element(k2)

print("\nUpdated directed matrix:\n")
print_matrix(new_matrix_dir)
get_graph_new_info(new_matrix_dir)

# draw_graph(matrix_dir, vertexes, 1)
# draw_graph(matrix_undir, vertexes, 0)
# draw_graph(new_matrix_dir, vertexes, 1)   