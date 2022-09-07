import numbers


class Matrix:
	def __init__(self, dims: (int, int), data: [float]):
		# If the amount of data provided does
		# not fit within the dimensions, error
		if len(data)/dims[0] != dims[1]:
			raise ValueError(
					f"Dimensions {dims} do not match data len ({len(data)})")
		self.dims = dims
		self.data = data

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
		if not isinstance(val, numbers.Number):
			raise ValueError(
                f"Error assigning new value to matrix cell. New value has type\
 {type(val)}, which is not a number type.")
 
		index_0, index_1 = index
		if index_0 < 0:
			index_0 = self.dims[0]+index_0
		if index_1 < 0:
			index_1 = self.dims[1]+index_1
		
		item_index = index_0 + self.dims[0]*index_1
		#print(item_index)
		if item_index > self.dims[0]*self.dims[1]:
			raise IndexError(f"Index [{index[0]}, {index[1]}] out of range")
		self.data[item_index] = val

	# Add `num` to every cell in row `row_index`
	def rowadd(self, row_index: int, num: float):
		for i in range(self.dims[0]):

			self[i, row_index] += num
			#print(self[i, row_index])

	# Add `num` to every cell in column `col_index`
	def coladd(self, col_index: int, num: float):
		for j in range(self.dims[1]):
			print(j)
			self[col_index, j] += num

	# Multiply every cell in row `row_index` by `num`
	def rowmul(self, row_index: int, num: float):
		for i in range(self.dims[0]):
			self[i, row_index] *= num

	# Multiply every cell in column `col_index` by `num`
	def colmul(self, col_index: int, num: float):
		for j in range(self.dims[1]):
			self[col_index, j] *= num


	def __repr__(self):
		output = ""
		for j in range(self.dims[1]):
			for i in range(self.dims[0]):
				output += str(self[i, j])
				output += ' '
			output += "\n"

		return output

class M(numbers.Number):
    # M class is a number with two values.
    # One regular number value, and another Big M value.
    def __init__(self, num_val, m_val):
        self.num_val = num_val
        self.m_val = m_val

    def __repr__(self):
        if self.m_val < 0:
            return f"({self.num_val} - {abs(self.m_val)}M)"
        return f"({self.num_val} + {self.m_val}M)"

    def __gt__(self, other):
        if isinstance(other, M):
            return (self.m_val > other.m_val) or (self.m_val == other.m_val and
                                                  self.num_val > other.num_val)

        return True

    def __lt__(self, other):
        if isinstance(other, M):
            return (self.m_val > other.m_val) or (self.m_val == other.m_val and
                                                  self.num_val > other.num_val)
        return False

    def __gte__(self, other):
        if isinstance(other, M):
            return (self.m_val >= other.m_val) or (self.m_val == other.m_val and
                                                  self.num_val >= other.num_val)

        return True

    def __lte__(self, other):
        if isinstance(other, M):
            return (self.m_val <= other.m_val) or (self.m_val == other.m_val and
                                                  self.num_val <= other.num_val)

        return False

    def __eq__(self, other):
        if isinstance(other, M):
            return self.m_val == other.m_val and self.num_val == other.num_val
        return False


    def __add__(self, other):
        if isinstance(other, M):
            self.m_val += other.m_val
            self.num_val += other.num_val
            return self
        self.num_val += other
        return self


    def __sub__(self, other):
        if isinstance(other, M):
            self.m_val -= other.m_val
            self.num_val -= other.num_val
            return self
        self.num_val -= other
        return self
    

    def __mul__(self, other):
        if isinstance(other, M):
            self.m_val *= other.m_val
            self.num_val *= other.num_val
            return self
        self.num_val *= other
        return self
    

    def __div__(self, other):
        if isinstance(other, M):
            self.m_val *= other.m_val
            self.num_val *= other.num_val
            return self
        self.num_val *= other
        return self
