from matrix import Matrix

dims = [(9, 5)]

start_data = [
[1,  1,  2,   1,   0,   0,  0,  0,   10,
2, -3,  1,   0,  -1,   0,  1,  0,    5,
1,  1,  0,   0,   0,  -1,  0,  1,    8,
-3, 2, -1,   0,   0,   0,  0,  0,    0,
-3, 2, -1,   0,   1,   1,  0,  0,  -13]


        ]

end_data = [
[0, 0, 2, 1, 0, 1, 0, -1, 2,
 1, 1, 2, 1, 0, 0, 0,  0, 10,
 0, 5, 3, 2, 1, 0,-1,  0, 15,
 0, 5, 5, 3, 0, 0, 0,  0, 30]
        ]

start_matrices = [Matrix(dim, data) for data, dim in zip(start_data, dims)]
end_matrices = [Matrix((dim[0], dim[1]-1), data) for data, dim in zip(end_data, dims)]
