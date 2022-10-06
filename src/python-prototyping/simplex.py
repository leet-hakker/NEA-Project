from M import M
from math import inf


def pivot_column(matrix, objective_row=-1):
    objective_row = [
        matrix[i, objective_row] for i in range(matrix.dims[0] - 1)
    ]


    return objective_row.index(min(objective_row))


def pivot_row(matrix, column, two_stage=False):
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


def isoptimal(matrix, objective_row=-1):
    row = matrix.row(objective_row)[:-1]
    minimum = row[0]

    for item in row:
        if item < minimum:
            minimum = item


    if isinstance(minimum, M):
        return minimum.m_val > 0 or minimum == M(0,0)

    return minimum >= 0


def simplex(matrix,
            column_names,
            row_names,
            objective_row=-1,
            two_stage=False,
            show_changes=False):

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
            yield matrix, row_names, (column, row)

    if not show_changes:
        yield matrix, row_names, (-1, -1)


def two_stage_simplex(matrix, column_names, row_names, show_changes=False):
    for matrix, row_names, pivot_cell in simplex(matrix,
                                                 column_names,
                                                 row_names,
                                                 objective_row=-1,
                                                 two_stage=True,
                                                 show_changes=show_changes):
        if show_changes:
            yield matrix, row_names, pivot_cell

    # Remove I row
    matrix.removerow(-1)
    row_names.pop(-1)

    for matrix, row_names, pivot_cell in simplex(matrix,
                                                 column_names,
                                                 row_names,
                                                 show_changes=show_changes):
        yield matrix, row_names, pivot_cell
