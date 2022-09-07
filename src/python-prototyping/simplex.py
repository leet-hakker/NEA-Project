from lib import Matrix, M

def pivot_column(matrix):
	objective_row = [matrix[i, -1] for i in range(matrix.dims[0]-1)]

	return objective_row.index(min(objective_row))

def pivot_row(matrix, column):
	thetas = []
	indices = []
	for j in range(matrix.dims[1]-1):
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


def simplex(matrix):
	column = pivot_column(matrix)
	row = pivot_row(matrix, column)

	matrix.rowmul(row, 1/matrix[column, row])
	for j in range(matrix.dims[1]):
		if j == row:
			continue
		for i in range(matrix.dims[0]):
			matrix[i, j] -= matrix[row, j]*matrix[i, column]

	return matrix

column_names = ["x", "y", "z", "r", "s", "t", "Value"]
row_names = ["r", "s", "y", "P"]

		# x	   y    z   r  s    t   Value       Theta
data = [-0.25, 0, -0.5, 1, 0, -0.75, 8,   # r    -16
		 2.5,  0,  2,   0, 1, -0.5,  92,  # s	  46
		 0.75, 1,  0.5, 0, 0,  0.25, 24,  # y     48
		 3,    0, -6,   0, 0,  5,    480] # P


mat = Matrix((len(column_names), len(row_names)), data)


print(simplex(mat))
