from M import M
from matrix import Matrix

dims = [(8, 4)]

start_data = [
[2, 1, 1, 1, 0, 0, 0, 20,
1, -2, -1, 0, 1, 0, 0, 7,
1, 0, 0, 0, 0, -1, 1, 4,
M(-1, -1), 1, -1, 0, 0, M(0, 1), 0, M(0, -4)]
]

end_data = [

[0, 1, 1, 1, 0, 2, -2, 12,
0, -1, 0, 1, 1, 3, -3, 15,
1, 0, 0, 0, 0, -1, 1, 4,
0, 2, 0, 1, 0, 1, M(-1, 1), 16]

]

start_matrices = [Matrix(dim, data) for data, dim in zip(start_data, dims)]
end_matrices = [Matrix(dim, data) for data, dim in zip(end_data, dims)]
