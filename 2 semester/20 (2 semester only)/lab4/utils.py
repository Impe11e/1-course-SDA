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