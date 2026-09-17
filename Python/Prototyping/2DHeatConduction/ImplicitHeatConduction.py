import numpy as np
from scipy.sparse import lil_matrix
from scipy.sparse.linalg import spsolve

import BoundaryCondition as BC
import Field
from CSVExporter import CSVExporter


"""
Discretization

for alpha = 1

(T(xi, yi, tn+1) - T(xi, yi, tn)) / dt = (T(xi+1, yi, tn+1) - 2 * T(xi, yi, tn+1) + T(xi-1, yi, tn+1) / dx**2
                                       + (T(xi, yi+1, tn+1) - 2 * T(xi, yi, tn+1) + T(xi, yi-1, tn+1) / dy**2

where   rd = dt * (1 + 2 / dx**2 + 2 / dy**2)
        rx = dt / dx**2
        ry = dt / dy**2

then:

rd * T(xi, yi, tn+1) - rx * (T(x+1, y, tn+1) + T(x-1, y, tn+1)
                     - ry * (T(x, y+1, tn+1) + T(x, y-1, tn+1)
                     = T(x, y, tn)

"""

class ImplicitSolver:
    def __init__(self, material_properties, simulation_properties):
        self.material_properties = material_properties
        self.simulation_properties = simulation_properties

    def _build_matrix(self, mesh, rx, ry):
        number_of_unknowns = mesh.nx * mesh.ny
        matrix = lil_matrix((number_of_unknowns, number_of_unknowns))

        def index(xi, yi):
            return (xi - 1) * mesh.ny + (yi - 1)

        for xi in range(1, mesh.nx + 1):
            for yi in range(1, mesh.ny + 1):
                row = index(xi, yi)
                diagonal = 1.0 + 2.0 * rx + 2.0 * ry
                matrix[row, row] = diagonal

                if xi > 1:
                    matrix[row, index(xi - 1, yi)] = -rx

                if xi < mesh.nx:
                    matrix[row, index(xi + 1, yi)] = -rx

                if yi > 1:
                    matrix[row, index(xi, yi - 1)] = -ry
                else:
                    diagonal -= ry #Due to neumann condition

                if yi < mesh.ny:
                    matrix[row, index(xi, yi + 1)] = -ry
                else:
                    diagonal -= ry

                matrix[row, row] = diagonal

        return matrix.tocsr()

    def solve(self, mesh, final_result_path=""):
        T_top = 373.0
        T_bottom = 273.0
        T = Field.Field(mesh)
        T.initialize(lambda x, y: 300.0)

        bc_top = BC.Direchlet(T.field[0, :], lambda dx: T_top)
        bc_bottom = BC.Direchlet(T.field[-1, :], lambda dx: T_bottom)
        bc_left = BC.Neuman(T.field[:, 0], lambda dy, aligned_cell: aligned_cell, T.field[:, 1])
        bc_right = BC.Neuman(T.field[:, -1], lambda dy, aligned_cell: aligned_cell, T.field[:, -2])

        dt = self.simulation_properties.dt
        alpha = (self.material_properties.thermal_conductivity /
                 (self.material_properties.density * self.material_properties.specific_heat))
        rx = alpha * dt / mesh.dx**2
        ry = alpha * dt / mesh.dy**2
        matrix = self._build_matrix(mesh, rx, ry)
        exporter = CSVExporter()

        def index(xi, yi):
            return (xi - 1) * mesh.ny + (yi - 1)

        for timestep in range(self.simulation_properties.timesteps):
            T.set_boundary_conditions(bc_top, bc_bottom, bc_left, bc_right)
            previous = T.field.copy()
            rhs = previous[1:mesh.nx + 1, 1:mesh.ny + 1].reshape(-1).copy()

            for yi in range(1, mesh.ny + 1):
                rhs[index(1, yi)] += rx * T_top
                rhs[index(mesh.nx, yi)] += rx * T_bottom

            solution = spsolve(matrix, rhs)
            T.field[1:mesh.nx + 1, 1:mesh.ny + 1] = solution.reshape(mesh.nx, mesh.ny)

            if (self.simulation_properties.should_export_results
                    and not final_result_path
                    and timestep % self.simulation_properties.export_frequency == 0):
                exporter.export(f"Results/T/{timestep}.csv", T.field)

        if self.simulation_properties.should_export_results:
            filename = final_result_path or f"Results/T/{self.simulation_properties.timesteps}.csv"
            exporter.export(filename, T.field)
