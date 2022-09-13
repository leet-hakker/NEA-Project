from numbers import Rational, Number
from fractions import Fraction

class Matrix:
	def __init__(self, dims: (int, int), data: [float]):
		# If the amount of data provided does
		# not fit within the dimensions, error
		if len(data)/dims[0] != dims[1]:
			raise ValueError(
					f"Dimensions {dims} do not match data len ({len(data)})")
		self.dims = dims
		self.data = [Fraction(num) for num in data]

	# Returns the value at index `index`
	def __getitem__(self, index: (int, int)):
		index_0, index_1 = index
		if index_0 < 0:
			index_0 = self.dims[0]+index_0
		if index_1 < 0:
			index_1 = self.dims[1]+index_1
		
		item_index = index_0 + self.dims[0]*index_1
		
		if item_index > self.dims[0]*self.dims[1]:
			raise IndexError(f"Index [{index[0]}, {index[1]}] out of range")
		return self.data[item_index]

	# Sets the value at `index` to `val`
	def __setitem__(self, index: (int, int), val: float):
		# If val is wrong type, error
		if not isinstance(val, Number):
			raise ValueError(
				f"Error assigning new value to matrix cell. New value has type\
 {type(val)}, which is not a number type.")
 
		index_0, index_1 = index
		if index_0 < 0:
			index_0 = self.dims[0]+index_0
		if index_1 < 0:
			index_1 = self.dims[1]+index_1
		
		item_index = index_0 + self.dims[0]*index_1

		if item_index > self.dims[0]*self.dims[1]:
			raise IndexError(f"Index [{index[0]}, {index[1]}] out of range")
		self.data[item_index] = val


	def row(self, row_index):
		return MatrixRow([self[i, row_index] for i in range(self.dims[0])])


	def removerow(self, row_index):
		if row_index < 0:
			row_index = self.dims[1]+row_index
		
		start_index = self.dims[0]*row_index
		for i in range(self.dims[0]):
			self.data.pop(start_index)
		self.dims = (self.dims[0], self.dims[1]-1)

		assert len(self.data) == self.dims[0]*self.dims[1]


	def column(self, col_index):
		return MatrixCol([self[col_index, j] for j in range(self.dims[1])])


	# Add `num` to every cell in row `row_index`
	def rowadd(self, row_index: int, other: float):
		for i in range(self.dims[0]):

			if isinstance(other, Number):
				self[i, row_index] += other
			elif isinstance(other, list):
				self[i, row_index] += other[i]
			else:
				raise ValueError(f"Type of other is not number or list: {type(other)}")

	# Add `num` to every cell in column `col_index`
	def coladd(self, col_index: int, other: float):
		for j in range(self.dims[1]):

			if isinstance(other, Number):
				self[col_index, j] += other
			elif isinsance(other, list):
				self[col_index, j] += other[j]
			else:
				raise ValueError(f"Type of other is not number or list: {type(other)}")

	# Multiply every cell in row `row_index` by `num`
	def rowmul(self, row_index: int, other: float):
		for i in range(self.dims[0]):

			if isinstance(other, Number):
				self[i, row_index] *= other
			elif isinstance(other, list):
				self[i, row_index] *= other[i]
			else:
				raise ValueError(f"Type of other is not number or list: {type(other)}")

	# Multiply every cell in column `col_index` by `num`
	def colmul(self, col_index: int, other: float):
		for j in range(self.dims[1]):

			if isinstance(other, Number):
				self[col_index, j] *= other
			elif isinsance(other, list):
				self[col_index, j] *= other[j]
			else:
				raise ValueError(f"Type of other is not number or list: {type(other)}")


	def __repr__(self):
		output = ""
		length = [0 for i in range(self.dims[0])]
		for i in range(self.dims[0]):
			for j in range(self.dims[1]):
				if len(str(self[i, j])) > length[i]:
					length[i] = len(str(self[i, j]))
			
		for j in range(self.dims[1]):
			for i in range(self.dims[0]):
				output += f" {' '*(length[i]-len(str(self[i, j])))}{self[i, j]} "
			output += "\n"

		return output


class MatrixRow(list):
	def __getitem__(self, key):
		return super(MatrixRow, self).__getitem__(key)
	
	def __setitem__(self, key, val):
		return super(MatrixRow, self).__setitem__(key, val)

	def __mul__(self, other):
		return MatrixRow([self[i] * other for i in range(len(self))])


class MatrixCol(list):
	def __getitem__(self, key):
		return super(MatrixCol, self).__getitem__(key)
	
	def __setitem__(self, key):
		return super(MatrixCol, self).__setitem__(key)

	def __mul__(self, other):
		for i in range(len(self)):
			self[i] *= other


class DisplayMatrix():
	def __init__(self, matrix, col_names, row_names, changes=(-1, -1)):
		self.dims = (matrix.dims[0]+1, matrix.dims[1]+1)
		self.data = [" "]
		self.data.extend(col_names)
		self.changes = changes
		
		for i in range(len(row_names)):
			row = matrix.row(i)
			row.insert(0, row_names[i])
			self.data.extend(row)
		
		for i in range(len(self.data)):
			self.data[i] = str(self.data[i])

		if sum(changes) >= 0:
			self[changes[0]+1, changes[1]+1] = f"*{self[changes[0]+1, changes[1]+1]}*"

	# Returns the value at index `index`
	def __getitem__(self, index: (int, int)):
		index_0, index_1 = index
		if index_0 < 0:
			index_0 = self.dims[0]+index_0
		if index_1 < 0:
			index_1 = self.dims[1]+index_1
		
		item_index = index_0 + self.dims[0]*index_1
		
		if item_index > self.dims[0]*self.dims[1]:
			raise IndexError(f"Index [{index[0]}, {index[1]}] out of range")
		return self.data[item_index]

	# Sets the value at `index` to `val`
	def __setitem__(self, index: (int, int), val: str):
		index_0, index_1 = index
		if index_0 < 0:
			index_0 = self.dims[0]+index_0
		if index_1 < 0:
			index_1 = self.dims[1]+index_1
		
		item_index = index_0 + self.dims[0]*index_1

		if item_index > self.dims[0]*self.dims[1]:
			raise IndexError(f"Index [{index[0]}, {index[1]}] out of range")
		self.data[item_index] = val


	def __repr__(self):
		output = ""
		length = [0 for i in range(self.dims[0])]
		for i in range(self.dims[0]):
			for j in range(self.dims[1]):
				if len(str(self[i, j])) > length[i]:
					length[i] = len(self[i, j])
			
		for j in range(self.dims[1]):
			for i in range(self.dims[0]):
					output += f" {' '*(length[i]-len(self[i, j]))}{self[i, j]} "
			
			output += "\n"

		return output
