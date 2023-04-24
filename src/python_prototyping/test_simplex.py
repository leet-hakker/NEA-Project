from matrix import Matrix
from fractions import Fraction


dims = [(6, 3), (7, 4)]

start_data = [
[2, 2, 0, 1, 0, 5,
5, 3, 4, 0, 1, 15,
-10, -12, -8, 0, 0, 0],

[2, -3, 2, 1, 0, 0, 4,
    1, 2, 4, 0, 1, 0, 8,
    0, 1, -1, 0, 0, 1, 6,
    -3, -4, 5, 0, 0, 0, 0]
]

end_data = [
[1, 1, 0, Fraction(1/2), 0, Fraction(5/2),
Fraction(1/2), 0, 1, Fraction(-3/8), Fraction(1/4), Fraction(15/8),
6, 0, 0, 3, 2, 45],

[1, 0, Fraction(16, 7), Fraction(2, 7), Fraction(3, 7), 0, Fraction(32, 7),
    0, 1, Fraction(6, 7), Fraction(-1, 7), Fraction(2, 7), 0, Fraction(12, 7),
    0, 0, Fraction(-13, 7), Fraction(1, 7), Fraction(-2, 7), 1, Fraction(30, 7),
    0, 0, Fraction(107, 7), Fraction(2, 7), Fraction(17, 7), 0, Fraction(144, 7)]
]

start_matrices = [Matrix(dim, data) for data, dim in zip(start_data, dims)]
end_matrices = [Matrix(dim, data) for data, dim in zip(end_data, dims)]
