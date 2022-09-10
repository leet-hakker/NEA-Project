from lib import Matrix, DisplayMatrix, M

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


def isoptimal(matrix, objective_row=-1):
	return min(matrix.row(objective_row)) >= 0


def simplex(matrix, column_names, row_names, show_changes=False):
	while not isoptimal(matrix):
		column = pivot_column(matrix)
		row = pivot_row(matrix, column)

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

	

column_names = ["x", "y", "r", "s", "Value"]
row_names = ["r", "s", "P"]

		# x	   y   r   s  Value
data = [  5,   7,  1,  0,   70,   # r
		 10,   3,  0,  1,   60,   # s
		 -3,  -2,  0,  0,    0]   # P


mat = Matrix((len(column_names), len(row_names)), data)

for mat, row_names, pivot_cell in simplex(mat, 
										  column_names, 
										  row_names, 
										  show_changes=True):

	print(DisplayMatrix(mat, 
						column_names, 
						row_names, 
						changes=pivot_cell)
		 )
