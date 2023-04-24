from M import M
from matrix import Matrix
from math import inf


def pivot_column(matrix: Matrix, objective_row: int = -1) -> int:
    objective_row = [
        matrix[i, objective_row] for i in range(matrix.dims[0] - 1)
    ]

    return objective_row.index(min(objective_row))


def pivot_row(matrix: Matrix, column: int, two_stage: bool = False) -> int:
    thetas = []
    indices = []

    rows = [j for j in range(matrix.dims[1] - 1)]
    if two_stage:
        rows = [j for j in range(matrix.dims[1] - 2)]

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


def isoptimal(matrix: Matrix, objective_row: int = -1) -> bool:
    row = matrix.row(objective_row)[:-1]
    minimum = row[0]

    for item in row:
        if item < minimum:
            minimum = item

    if isinstance(minimum, M):
        return minimum.m_val > 0 or minimum == M(0, 0)

    return minimum >= 0


def simplex(matrix: Matrix,
            column_names: [str],
            row_names: [str],
            objective_row: int = -1,
            two_stage: bool = False,
            show_changes: bool = False) -> [Matrix, [str], [int, int]]:

    while not isoptimal(matrix, objective_row=objective_row):
        column = pivot_column(matrix, objective_row=objective_row)
        row = pivot_row(matrix, column, two_stage=two_stage)

        matrix.rowmul(row, 1 / matrix[column, row])

        row_names[row] = column_names[column]

        for i in range(matrix.dims[1]):
            if i == row:
                continue

            row_modifier = matrix.row(row) * (-matrix[column, i])

            matrix.rowadd(i, row_modifier)

        if show_changes:
            return matrix, row_names, (column, row)

    if not show_changes:
        return matrix, row_names, (-1, -1)


def two_stage_simplex(matrix: Matrix, column_names: [str], row_names: [str], show_changes: bool = False) -> [Matrix, [str], [int, int]]:
    while not isoptimal(matrix, objective_row=-1):
        matrix, row_names, pivot_cell = simplex(matrix,
                                                column_names,
                                                row_names,
                                                objective_row=-1,
                                                two_stage=True,
                                                show_changes=show_changes)
        if show_changes:
            return matrix, row_names, pivot_cell

    # Remove I row
    matrix.removerow(-1)
    row_names.pop(-1)

    return matrix, row_names, pivot_cell
