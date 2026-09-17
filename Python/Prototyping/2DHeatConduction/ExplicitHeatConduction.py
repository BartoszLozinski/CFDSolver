import Field
import BoundaryCondition as BC
from CSVExporter import CSVExporter

class ExplicitSolver():
    def __init__(self, material_properties, simulation_properties):
        self.material_properties = material_properties
        self.simulation_properties = simulation_properties

    # boundary conditions to fix 
    def solve(self, mesh, final_result_path=""):
        # y_tn+1_xi = r T_xi+1 + (1 - 2 * r) * T_xi + r * T_xi_-1
        #      
        # For now assume initial value equal to T_0
        T_top = 373
        T_bottom = 273
        T = Field.Field(mesh)  # Temperature [K]
        T.initialize(lambda x, y: 300)

        bc_top = BC.Direchlet(T.field[0, :], lambda dx: T_top)
        bc_bottom = BC.Direchlet(T.field[-1, :], lambda dx: T_bottom)
        bc_left = BC.Neuman(T.field[:, 0],
                            lambda dy, alignedCell: alignedCell, T.field[:, 1])
        bc_right = BC.Neuman(T.field[:, -1],
                             lambda dy, alignedCell: alignedCell, T.field[:, -2])

        dx = mesh.dx
        dy = mesh.dy
        dt = self.simulation_properties.dt
        alfa = self.material_properties.thermal_conductivity / (self.material_properties.density *
                                                                self.material_properties.specific_heat)
        rx = alfa * dt / dx**2
        ry = alfa * dt / dy**2

        if (rx + ry) > 0.5:
            print("rx + ry > 0.5. Timestep will be adjusted!")
            self.dt = 0.9 * dx**2 * dy**2 / (2 * alfa * (dx**2 + dy**2))
            dt = self.dt
            rx = alfa * dt / dx**2
            ry = alfa * dt / dy**2
            print(f'dt is updated to dt = {self.dt} [s]')

        exporter = CSVExporter()

        for timestep in range(self.simulation_properties.timesteps):
            T.set_boundary_conditions(bc_top, bc_bottom, bc_left, bc_right)
            T_previous = T.copy()

            for row in range(mesh.nx):
                xi = row + 1  # internal row with ghost cell offset
                for column in range(mesh.ny):
                    yi = column + 1  # internal column with ghost cell offset
                    T[xi, yi] = ((T_previous[xi + 1, yi] + T_previous[xi - 1, yi]) * rx +
                                 (T_previous[xi, yi + 1] + T_previous[xi, yi - 1]) * ry +
                                 (T_previous[xi, yi] * (1 - 2 * rx - 2 * ry)))

            if (self.simulation_properties.should_export_results
                    and not final_result_path
                    and timestep % self.simulation_properties.export_frequency == 0):
                exporter.export(f"Results/T/{timestep}.csv", T.field)

        if self.simulation_properties.should_export_results:
            filename = final_result_path or f"Results/T/{self.simulation_properties.timesteps}.csv"
            exporter.export(filename, T.field)
