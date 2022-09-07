from lib import Matrix, M

def pivot_column(matrix):
	objective_row = [matrix[i, -1] for i in range(matrix.dims[0]-1)]
	
	return objective_row.index(min(objective_row))

def pivot_row(matrix, column):
	theta = matrix[i, -1] / matrix[column, -1]


column_names = ["x", "y", "z", "r", "s", "t", "Value"]
row_names = ["r", "s", "y", "P"]

		# x	   y    z   r  s    t   Value
data = [-0.25, 0, -0.5, 1, 0, -0.75, 8,   # r
		 2.5,  0,  2,   0, 1, -0.5,  92,  # s
		 0.75, 1,  0.5, 0, 0,  0.25, 24,  # y
		 3,    0, -6,   0, 0,  5,    480] # P


mat = Matrix((len(column_names), len(row_names)), data)

# Should print 2
print(pivot_column(mat))
