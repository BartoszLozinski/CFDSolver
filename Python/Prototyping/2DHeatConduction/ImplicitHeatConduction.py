"""
Discretization

(T(xi, yi, tn+1) - T(xi, yi, tn)) / dt = (T(xi+1, yi, tn+1) - 2 * T(xi, yi, tn+1) + T(xi-1, yi, tn+1) / dx**2
                                       + (T(xi, yi+1, tn+1) - 2 * T(xi, yi, tn+1) + T(xi, yi-1, tn+1) / dy**2

"""

"""
# Copliot proposal

from scipy.sparse import lil_matrix
from scipy.sparse.linalg import spsolve

A = lil_matrix((number_of_unknowns, number_of_unknowns))
B = previous_temperature.copy()

for j in range(1, ny - 1):
    for i in range(1, nx - 1):
        row = (i - 1) + (j - 1) * (nx - 2)

        A[row, row] = 1 + 2 * rx + 2 * ry

        if i > 1:
            A[row, row - 1] = -rx

        if i < nx - 2:
            A[row, row + 1] = -rx

        if j > 1:
            A[row, row - (nx - 2)] = -ry

        if j < ny - 2:
            A[row, row + (nx - 2)] = -ry

T_new = spsolve(A.tocsr(), B)

"""
