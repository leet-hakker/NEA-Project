from matrix import Matrix, DisplayMatrix
from M import M
from math import inf
from datetime import datetime

def pivot_column(matrix, objective_row=-1):
	objective_row = [matrix[i, objective_row] for i in range(matrix.dims[0]-1)]

	return objective_row.index(min(objective_row))

def pivot_row(matrix, column, two_stage=False):
	thetas = []
	indices = []
	
	rows = [j for j in range(matrix.dims[1]-1)]
	if two_stage:
		rows = [j for j in range(matrix.dims[1]-2)]
	
	for j in rows:
		if matrix[column, j] == 0:
			theta = inf
		else:
			theta = matrix[-1, j] / matrix[column, j]
		if theta >= 0:
			thetas.append(theta)
			indices.append(j)
			
	
	index = indices[0]
	theta = thetas[0]
	for ind, thet in zip(indices, thetas):
		if thet < theta:
			theta = thet
			index = ind
	
	return index


def isoptimal(matrix, objective_row=-1):
	return min(matrix.row(objective_row)[:-1]) >= 0


def simplex(matrix, column_names, row_names, objective_row=-1, two_stage=False, show_changes=False):
	iters = 0
	while not isoptimal(matrix, objective_row=objective_row):
		column = pivot_column(matrix, objective_row=objective_row)
		row = pivot_row(matrix, column, two_stage=two_stage)

		matrix.rowmul(row, 1/matrix[column, row])

		row_names[row] = column_names[column]

		for i in range(matrix.dims[1]):
			if i == row:
				continue
			
			row_modifier = matrix.row(row)*(-matrix[column, i])
					
			matrix.rowadd(i, row_modifier)
		
		if show_changes:
			yield matrix, row_names, (column, row)
		
	
	if not show_changes:
		yield  matrix, row_names, (-1, -1)


def two_stage_simplex(matrix, column_names, row_names, show_changes=False):
	for matrix, row_names, pivot_cell in simplex(matrix, 
												 column_names,
												 row_names,
												 objective_row=-1,
												 two_stage=True,
												 show_changes=show_changes):
		yield matrix, row_names, pivot_cell

	# Remove I row
	matrix.removerow(-1)
	row_names.pop(-1)
	
	for matrix, row_names, pivot_cell in simplex(matrix,
												 column_names, 
												 row_names,
												 show_changes=show_changes):
		yield matrix, row_names, pivot_cell


#column_names = ["x", "y", "z", "r", "s", "t", "Value"]
#row_names = ["r", "s", "y", "P"]

		#   x     y      z     r    s      t    Value
#data = [ -0.25,   0,  -0.5,    1,   0,  -0.75,    8,   # r
#		   2.5,   0,     2,    0,   1,   -0.5,   92,   # s
#		  0.75,   1,   0.5,    0,   0,   0.25,   24,   # y
#		     3,   0,    -6,    0,   0,      5,  480]   # P

# Two stage matrix

#column_names = ["x", "y", "z", "s1", "s2", "s3", "a1", "a2", "Value"]
#row_names = ["s1", "s2", "a1", "P", "I"]

	#   x   y   z   s1   s2   s3  a1  a2  Value
#data = [1,  1,  2,   1,   0,   0,  0,  0,   10,  #  s1
#		2, -3,  1,   0,  -1,   0,  1,  0,    5,  #  a1
#		1,  1,  0,   0,   0,  -1,  0,  1,    8,  #  a2
#		-3, 2, -1,   0,   0,   0,  0,  0,    0,  #  P
#		-3, 2, -1,   0,   1,   1,  0,  0,  -13]  #  I

# Big M matrix

	  #      x      y   z  s1  s2     s3       a1      Value
#data = [    2,     1,  1,  1,  0,     0,       0,       20,    # s1
#            1,    -2, -1,  0,  1,     0,       0,        7,    # s2
#            1,     0,  0,  0,  0,    -1,       1,        4,    # a1
#        M(-1, -1), 1, -1,  0,  0,  M(0, 1),    0,   M(0, -4)]  # P

n_columns = int(input("How many columns? "))
n_rows = int(input("How many rows? "))

column_names = []
row_names = []

for col in range(n_columns):
	column_names.append(input(f"Column {col+1}: "))

for row in range(n_rows):
	row_names.append(input(f"Row {row+1}: "))

data = []

print("Enter data, row by row. Separate entrys with spaces.\nPress enter at the end of each row.")

for j in range(n_rows):
	_data = input("").split()

	for dat in _data:
		data.append(int(dat))

mat = Matrix((len(column_names), len(row_names)), data)


solver_idx = -1
solvers = [simplex, two_stage_simplex]
while solver_idx-1 not in (0, 1):
	solver_idx = int(input("""Which method do you want to use to solve?
Simplex Algorithm: 1
Two Stage Simplex Algorithm: 2

: """))

solver = solvers[solver_idx-1]

start = datetime.now()
for mat, row_names, pivot_cell in solver(mat, 
										  column_names, 
										  row_names, 
										  show_changes=True):

	print(DisplayMatrix(mat, 
						column_names, 
						row_names, 
						changes=pivot_cell)
		 )
time_taken = datetime.now() - start
print(time_taken)
