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
        item_index = self.dims[1]*index[0] + index[1]
        return self.data[item_index]

    # Sets the value at `index` to `val`
    def __setitem__(self, index: (int, int), val: float):
        # If val is wrong type, error
        if not isinstance(val, numbers.Number):
            raise ValueError(
                f"Error assigning new value to matrix cell. New value has type\
 {type(val)}, which is not a number type.")

        item_index = self.dims[1]*index[0] + index[1]
        self.data[item_index] = val

    # Add `num` to every cell in row `row_index`
    def rowadd(self, row_index: int, num: float):
        for i in range(self.dims[0]):
            self.data[self.dims[1]*i + row_index] += num

    # Add `num` to every cell in column `col_index`
    def coladd(self, col_index: int, num: float):
        for j in range(self.dims[1]):
            self.data[self.dims[1]*col_index + j] += num

    # Multiply every cell in row `row_index` by `num`
    def rowmul(self, row_index: int, num: float):
        for i in range(self.dims[0]):
            self.data[self.dims[1]*i + row_index] *= num

    # Multiply every cell in column `col_index` by `num`
    def colmul(self, col_index: int, num: float):
        for j in range(self.dims[1]):
            self.data[self.dims[1]*col_index + j] *= num


# This represents a matrix like such:
# | 1  3 |
# | 2  4 |
A = Matrix((2, 2), [1, 2, 3, 4])
# Should print [1,  3]
print([A[0, 0], A[1, 0]])
# Changes 1 to 10 and 3 to 30
A.rowmul(0, 10)
# Should print [10, 30]
print([A[0, 0], A[1, 0]])
# Should print [30, 4]
print([A[1, 0], A[1, 1]])
# Changes 30 to 15 and 4 to 2
A.colmul(1, 0.5)
# Should print [15, 2]
print([A[1, 0], A[1, 1]])
