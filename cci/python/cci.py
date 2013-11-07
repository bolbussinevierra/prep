#1.3 ----
def permutation(a,b):
    if len(a) != len(b):
        return False
    return sorted(a) == sorted(b)

#1.5 ----------------------------------
def count_compress(stream):
    last = stream[0]
    count = 1
    size = 0
    for i in range(1, len(stream)):
        if stream[i] == last:
            count += 1
        else:
            size += 1 + len(str(count))
            count = 1
    size += 1 + len(str(count))

def compress(stream):
    size = count_compress(stream)
    if size >= len(stream):
        return stream

    compressed = ""
    first = stream[0]
    count = 1
    for i in range(1, len(stream)):
        if stream[i] == first:
            count += 1
        else:
            compressed += first + str(count)
            first = stream[i]
            count = 1
    compressed += first + str(count)
    return compressed
# 1.6 -----------------------------------------
import sys
 
#create a N X N matrix
def generate_matrix(n):
    matrix = []
    for i in range(n):
        inside = []
        for j in range(n):
            inside.append(j + i + 2)
        matrix.append(inside)
    return matrix
 
#print the matrix
def print_matrix(m):
    for row in m:
        print row
    print

def rotate_matrix_90(n):
    matrix = generate_matrix(n)
    print_matrix(matrix)

    layers = (n/2)
    for layer in range(0, layers): # range is end-enclusive
        start = layer
        end = n - 1 - layer
        for i in range(start, end):
            offset = i - start
            top = matrix[start][i]
            matrix[start][i] = matrix[end - offset][start]
            matrix[end - offset][start] = matrix[end][end - offset]
            matrix[end][end - offset] = matrix[i][end]
            matrix[i][end] = top

    print_matrix(matrix) 

