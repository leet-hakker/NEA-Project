import test_simplex, test_two_stage, test_big_m
from simplex import simplex, two_stage_simplex


solvers = [[test_simplex, simplex], [test_two_stage, two_stage_simplex], [test_big_m, simplex]]

def test_one(start_matrix, end_matrix, solver):
    columns = [i for i in range(start_matrix.dims[0])]
    rows = [i for i in range(start_matrix.dims[1])]

    for calculated_end_matrix, _, _ in solver(start_matrix, columns, rows):
        for calculated_mat_item, end_mat_item in zip(calculated_end_matrix.data, end_matrix.data):
            try:
                assert calculated_mat_item == end_mat_item
            except:
                print(calculated_mat_item)
                print(calculated_end_matrix)
                print(end_matrix)
                raise

def test_all(start_matrices, end_matrices, solver):
    print(f"Testing {solver.__name__}...")
    for start, end in zip(start_matrices, end_matrices):
        test_one(start, end, solver)

    return True

for solver in solvers:
    test_all(solver[0].start_matrices, solver[0].end_matrices, solver[1])
