from lib import Matrix

dims = (7, 4)
data = [
    -0.25, 0, -0.5, 1, 0, -0.75, 8, 2.5, 0, 2, 0, 1, -0.5, 92, 0.75, 1, 0.5, 0,
    0, 0.25, 24, 3, 0, -6, 0, 0, 5, 480
]

mat = Matrix(dims, data)

output = ""
length = [0 for i in range(dims[0])]
for i in range(dims[0]):
    for j in range(dims[1]):
        if len(str(mat[i, j])) > length[i]:
            length[i] = len(str(mat[i, j]))

for j in range(dims[1]):
    for i in range(dims[0]):
        output += f" {' '*(length[i]-len(str(mat[i, j])))}{mat[i, j]} "
    output += "\n"

print(output)
