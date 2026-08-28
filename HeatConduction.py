import numpy as np
import matplotlib.pyplot as plt

"""
density * specific_heat * dT / dtime = thermal_conductivity * Laplacian(T) + HeatSource

For now 1D equation - to be developed for 2D and better architecture
Steady state - ok
Transient - TODO
heat Source term - including convection - TODO
"""

# y_i1 = y_(i+1)
# y_i_1 = y_(i-1)
def second_order_derivative_central_diff(y_i1, y_i, y_i_1, dx):
    return (y_i1 - 2 * y_i + y_i_1) / (dx ** 2)

# Discrete equation will look like:

# to match equations orders
# k * (y_i1 - 2 * y_i + y_i_1) / (dx ** 2) = rho * cp (y_i - y_i_1) / dt      // * dx**2 * 2dt
# k * dt * (y_i1 - 2 * y_i + y_i_1) = rho * cp * dx**2 * (y_i - y_i_1)
# y_i1 * a + y_i * b + y_i_1 * c = d

# d = 0 
# Simplified:
# y_i1 - 2 * y_i + y_i = 0


class MaterialProperties:
    def __init__(self, thermal_conductivity, density, specific_heat):
        self.thermal_conductivity = thermal_conductivity
        self.density = density
        self.specific_heat = specific_heat


class ImplicitSolver():
    def __init__(self, material_properties, dx, dt, x_0, x_end, T_0, T_end):
        self.material_properties = material_properties
        self.dx = dx
        self.dt = dt
        self.T_0 = T_0
        self.T_end = T_end
        self.X = np.linspace(x_0, x_end, int((x_end - x_0) / dx) + 1)

    def generate_2nd_order_pde_matrix(self, a, b, c):
        # solves
        # y_i1 * a + y_i * b + y_i_1 * c
        # matrix of coefficient will look like:
        # x1    x2      x3      x4      x5      =   T
        # b     c       0       0       0       =   -a * T_0 + d
        # a     b       c       0       0       =   d
        # 0     a       b       c       0       =   d
        # 0     0       a       b       c       =   d
        # 0     0       0       a       b       =   -c * T_end + d

        InnerArray = np.zeros((len(self.X) - 2, len(self.X) - 2))
        for i in range(len(self.X) - 2):
            InnerArray[i][i] = b
            if i > 0:
                InnerArray[i][i - 1] = a
            if i < len(self.X) - 3:
                InnerArray[i][i + 1] = c

        return InnerArray

    # direchlet condition only right now
    def generate_RHS_for_2nd_order_pde(self, a, c, d, RHS_previous_timestep):
        RHS = np.zeros(len(self.X) - 2)

        for i in range(len(RHS)):
            RHS[i] = RHS_previous_timestep[i] + d

        RHS[0] -= a * self.T_0
        RHS[-1] -= c * self.T_end

        return RHS

    def solve(self, timesteps, should_plot = False, plot_interval = 10):
        r = self.material_properties.thermal_conductivity * self.dt / (self.material_properties.density * self.material_properties.specific_heat * self.dx**2)
        y_i_plus1_coeff = -r
        y_i_coeff = 1 + 2 * r
        y_i_minus1_coeff = -r

        # For now assume initial value equal to T_0
        T = np.linspace(T_0, T_0, len(self.X))
        T[-1] = T_end

        T_inner = T[1: -1].copy()
        Array = self.generate_2nd_order_pde_matrix(y_i_minus1_coeff, y_i_coeff, y_i_plus1_coeff)
        for timestep in range(timesteps):
            RHS = self.generate_RHS_for_2nd_order_pde(y_i_minus1_coeff, y_i_plus1_coeff, 0, T_inner)
            T_inner = np.linalg.solve(Array, RHS)
            T = np.concatenate([[T_0], T_inner, [T_end]])

            #lets plot internally for now
            if should_plot and (timestep % plot_interval == 0):
                plt.plot(self.X, T, label=f"timestep: {timestep}")
                plt.xlabel("x [m]")
                plt.ylabel("T [K]")
                plt.title("Solution of steady state conduction")
                plt.legend()
                plt.grid()
                plt.show()


# Stainless steel
material_properties = MaterialProperties(16.0, 7850, 500)

x_0 = 0.0 # m 
x_end = 1.0 # m
T_0 = 1.0 # K
T_end = 0.0 # K
dx = 0.05 # m
dt = 360# s
timesteps = 100

solver = ImplicitSolver(material_properties, dx, dt, x_0, x_end, T_0, T_end)
solver.solve(timesteps, True)
