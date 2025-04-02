def get_matrix(rows, cols):
    print(f"Enter elements for a {rows}x{cols} matrix")
    matrix = []
    for _ in range(rows):
        row = list(map(int, input().split()))
        if len(row) != cols:
            print("Error: please enter correct number of columns")
            return None
        matrix.append(row)
    return matrix


def add_matrices(matrix1, matrix2):
    rows, cols = len(matrix1), len(matrix1[0])
    result = [[matrix1[i][j] + matrix2[i][j] for j in range(cols)] for i in range(rows)]
    return result


def print_matrix(matrix):
    for row in matrix:
        print(" ".join(map(str, row)))


rows = int(input("Enter number of rows :"))
cols = int(input("Enter number of column :"))
print("Matrix 1")
matrix1 = get_matrix(rows, cols)
if matrix1 is None:
    exit()
print("Matrix2")
matrix2 = get_matrix(rows, cols)
if matrix2 is None:
    exit()
result_matrix = add_matrices(matrix1, matrix2)
print("Resulted Matrix:")
print_matrix(result_matrix)
