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