from simplex import simplex, two_stage_simplex
from matrix import Matrix, DisplayMatrix
from fractions import Fraction

def process_into_m(data):
    data = data.replace(" ", "")
    num_val_str = ""
    m_val_str = ""
    data_list = []


    chunk = ""
   
    if '-' in data:
        if data.count('-') == 2:
            data_list = data.split('-')
            
    elif '+' in data:
        pass
    else:
        return ValueError("Input for M value invalid.")




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
        if "M" in dat:
            data.append(process_into_m(dat))
            

        else:
            data.append(Fraction(dat))

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
