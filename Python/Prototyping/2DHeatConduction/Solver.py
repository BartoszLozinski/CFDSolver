import Field
import BoundaryCondition as BC
import numpy as np
import matplotlib.pyplot as plot

class MaterialProperties:
    def __init__(self, thermal_conductivity, density, specific_heat):
        self.thermal_conductivity = thermal_conductivity
        self.density = density
        self.specific_heat = specific_heat

class ExplicitSolver():
    def __init__(self, material_properties, dt):
        self.material_properties = material_properties
        self.dt = dt

    # boundary conditions to fix 
    def solve(self, mesh, timesteps, should_plot = False, plot_interval = 10):
        # y_tn+1_xi = r T_xi+1 + (1 - 2 * r) * T_xi + r * T_xi_-1
        
        # to be updated
        # r = self.material_properties.thermal_conductivity * self.dt / (self.material_properties.density * self.material_properties.specific_heat * self.dx**2)
        # y_i_plus1_coeff = r
        # y_i_coeff = 1 - 2 * r
        # y_i_minus1_coeff = r

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
        dt = self.dt
        alfa = 1  # 1 is instead of providing material properties for simplicity
        rx = alfa * dt / dx**2
        ry = alfa * dt / dy**2

        if (rx + ry) > 0.5:
            print("rx + ry > 0.5. Timestep will be adjusted!")
            self.dt = 0.9 * dx**2 * dy**2 / (2 * alfa * (dx**2 + dy**2))
            dt = self.dt
            rx = alfa * dt / dx**2
            ry = alfa * dt / dy**2
            print(f'dt is updated to dt = {self.dt} [s]')

        # plotting only
        x = np.linspace(0, (mesh.nx + 1) * mesh.dx, mesh.nx)
        y = np.linspace(0, (mesh.ny + 1) * mesh.dy, mesh.ny)
        X, Y = np.meshgrid(x, y)
        fig, ax = plot.subplots()
        cbar = None
        meshplot = None

        for timestep in range(timesteps):
            T.set_boundary_conditions(bc_top, bc_bottom, bc_left, bc_right)
            T_previous = T.copy()

            for row in range(mesh.nx):
                xi = row + 1  # internal row with ghost cell offset
                for column in range(mesh.ny):
                    yi = column + 1  # internal column with ghost cell offset
                    T[xi, yi] = ((T_previous[xi + 1, yi] + T_previous[xi - 1, yi]) * dt / dx**2 +
                                 (T_previous[xi, yi + 1] + T_previous[xi, yi - 1]) * dt / dy**2 +
                                 (T_previous[xi, yi] * (1 - 2 * rx - 2 * ry)))

            # lets plot internally for now

            if should_plot and (timestep % plot_interval == 0):
                T2d_plot = T.field[1:-1, 1:-1]  # without ghost cells
                T2d_plot = T2d_plot.T

                if meshplot is None:
                    meshplot = ax.pcolormesh(X, Y, T2d_plot, cmap="jet", shading="auto", vmin=T_bottom, vmax=T_top)
                    cbar = fig.colorbar(meshplot, ax=ax, label="Temperature [K]")
                else:
                    meshplot.set_array(T2d_plot.ravel())
                    meshplot.set_clim(T_bottom, T_top)
                    meshplot.set_array(T2d_plot.ravel())

                ax.set_xlabel("x [m]")
                ax.set_ylabel("y [m]")
                ax.set_title(f"2D Temperature Field at timestep {timestep}")

                fig.canvas.draw_idle()
                plot.pause(0.001)
