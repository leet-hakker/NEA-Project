from simplex import simplex, two_stage_simplex
from matrix import Matrix, DisplayMatrix


n_columns = int(input("How many columns? "))
n_rows = int(input("How many rows? "))

column_names = []
row_names = []

for col in range(n_columns):
    column_names.append(input(f"Column {col+1}: "))

for row in range(n_rows):
    row_names.append(input(f"Row {row+1}: "))

data = []

print(
    """Enter data, row by row. Separate entrys with spaces.
    Press enter at the end of each row."""
)

for j in range(n_rows):
    _data = input("").split()

    for dat in _data:
        data.append(int(dat))

mat = Matrix((len(column_names), len(row_names)), data)

solver_idx = -1
solvers = [simplex, two_stage_simplex]
while solver_idx - 1 not in (0, 1):
    solver_idx = int(
        input("""Which method do you want to use to solve?
Simplex Algorithm: 1
Two Stage Simplex Algorithm: 2

: """))

solver = solvers[solver_idx - 1]

for mat, row_names, pivot_cell in solver(mat,
                                         column_names,
                                         row_names,
                                         show_changes=True):

    print(DisplayMatrix(mat, column_names, row_names, changes=pivot_cell))
