import math
import random

def print_array(arr, text, separator):
    print(text, end = " ")
    if(len(arr) == 0):
        print("no such vertexes", end=" ")
        print()
    else:
        for i in range(len(arr)):
            print(arr[i], end=separator)
        print()

def print_matrix(matrix):
    for row in matrix:
        for element in row:
            print(element, end=" ")
        print()

def matrix_multiply(A, B):
    n = len(A)
    result = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                result[i][j] += A[i][k] * B[k][j]
    return result

def matrix_add(A, B):
    n = len(A)
    result = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            result[i][j] = A[i][j] + B[i][j]
    return result


def get_weights(matrix_undir):
    vertexes = len(matrix_undir)
    B = [[0] * vertexes for _ in range(vertexes)]
    C = [[0] * vertexes for _ in range(vertexes)]
    D = [[0] * vertexes for _ in range(vertexes)]
    H = [[0] * vertexes for _ in range(vertexes)]
    W = [[0] * vertexes for _ in range(vertexes)]

    for i in range(vertexes):
        for j in range(vertexes):
            B[i][j] = random.random() * 2

    for i in range(vertexes):
        for j in range(vertexes):
            C[i][j] = math.ceil(100 * B[i][j] * matrix_undir[i][j])


    for i in range(vertexes):
        for j in range(vertexes):
            if(C[i][j] > 0):
                D[i][j] = 1


    for i in range(vertexes):
        for j in range(vertexes):
            if(D[i][j] != D[j][i]):
                H[i][j] = 1

    for i in range(vertexes):
        for j in range(vertexes):
            val = C[i][j] * (D[i][j] + H[i][j] * (i < j))
            if(i == j): 
                W[i][j] = W[j][i] = 0
            elif(val == 0):
                W[i][j] = W[j][i] = math.inf
            else:
                W[i][j] = W[j][i] = val
           
    return W